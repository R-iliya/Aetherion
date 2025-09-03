#include "core/hash_map.h"
#include "core/thread.h"
#include "core/delegate.h"
#include "core/os.h"
#include "core/profiler.h"
#include "core/string.h"
#include "file_system_watcher.h"
#include <sys/inotify.h>
#include <sys/select.h>
#include <unistd.h>


namespace Aetherion
{


struct FileSystemWatcherImpl;



struct FileSystemWatcherTask : Aetherion::Thread
{
	FileSystemWatcherTask(const char* path,
        FileSystemWatcherImpl& _watcher,
		Aetherion::IAllocator& _allocator)
		: Thread(_allocator)
		, watcher(_watcher)
		, watched(_allocator)
		, allocator(_allocator)
	{
		Aetherion::copyString(this->path, path);
		int len = Aetherion::stringLength(path);
		if(len > 0 && path[len - 1] != '/') Aetherion::catString(this->path, "/");
	}


	int task() override;

    void cancel() {
        finished = true;
        close(fd);
    }

    Aetherion::IAllocator& allocator;
    FileSystemWatcherImpl& watcher;
	volatile bool finished = false;
	char path[MAX_PATH];
	Aetherion::HashMap<int, Aetherion::StaticString<MAX_PATH> > watched;
	int fd;
};


struct FileSystemWatcherImpl : FileSystemWatcher
{
	explicit FileSystemWatcherImpl(Aetherion::IAllocator& _allocator)
		: allocator(_allocator)
		, task(nullptr)
	{
	}


    ~FileSystemWatcherImpl()
    {
        if (task)
        {
            task->cancel();
            task->destroy();
            AETHERION_DELETE(allocator, task);
        }
    }


    bool start(const char* path)
    {
        task = AETHERION_NEW(allocator, FileSystemWatcherTask)(path, *this, allocator);
        if (!task->create("FileSystemWatcherTask", true))
        {
            AETHERION_DELETE(allocator, task);
            task = nullptr;
            return false;
        }
        return true;
    }


	virtual Aetherion::Delegate<void(const char*)>& getCallback() { return callback; }


    FileSystemWatcherTask* task;
	Aetherion::Delegate<void(const char*)> callback;
	Aetherion::IAllocator& allocator;
};


UniquePtr<FileSystemWatcher> FileSystemWatcher::create(const char* path, Aetherion::IAllocator& allocator)
{
	UniquePtr<FileSystemWatcherImpl> watcher = UniquePtr<FileSystemWatcherImpl>::create(allocator, allocator);
	if(!watcher->start(path))
    {
        return UniquePtr<FileSystemWatcher>();
    }
	return watcher;
}


static void addWatch(FileSystemWatcherTask& task, const char* path, int root_length)
{
	if (!os::dirExists(path)) return;
	
    int wd = inotify_add_watch(task.fd, path, IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO | IN_CLOSE_WRITE);
    task.watched.insert(wd, path + root_length);

    auto iter = os::createFileIterator(path, task.allocator);
    os::FileInfo info;
    while (os::getNextFile(iter, &info))
    {
        if (!info.is_directory) continue;
		if (Aetherion::equalStrings(info.filename, ".")) continue;
		if (Aetherion::equalStrings(info.filename, "..")) continue;

        Aetherion::StaticString<MAX_PATH> tmp(path, info.filename, "/");
        addWatch(task, tmp, root_length);
    }
    os::destroyFileIterator(iter);
}


static void getName(FileSystemWatcherTask& task, inotify_event* event, char* out, int max_size)
{
    auto iter = task.watched.find(event->wd);

    if (iter == task.watched.end())
    {
        Aetherion::copyString(Span(out, max_size), event->name);
        return;
    }

    Aetherion::copyString(Span(out, max_size), iter.value());
    Aetherion::catString(Span(out, max_size), event->name);
}


int FileSystemWatcherTask::task()
{
    fd = inotify_init();
    if (fd == -1) return false;

	int root_length = Aetherion::stringLength(path);
    addWatch(*this, path, root_length);

    char buf[4096];
    while (!finished)
    {
		fd_set rfds;
		FD_ZERO (&rfds);
		FD_SET (fd, &rfds);
		timeval timeout;
		timeout.tv_sec=0;
		timeout.tv_usec=100000;

		if(select(FD_SETSIZE, &rfds, NULL, NULL, &timeout) > 0)
		{
            int r = read(fd, buf, sizeof(buf));
            if (finished) return 0;
            if(r == -1) return 1;
            auto* event = (inotify_event*)buf;

            while ((char*)event < buf + r)
            {
                char tmp[MAX_PATH];
                getName(*this, event, tmp, Aetherion::lengthOf(tmp));
                if (event->mask & IN_CREATE) addWatch(*this, tmp, root_length);
                watcher.callback.invoke(tmp);

                event = (inotify_event*)((char*)event + sizeof(*event) + event->len);
            }
        }
    }

    return close(fd) != -1;
}


} // namespace Aetherion