class Aio {
	Buffer * buffer;
	aiocb * aio;
	pthread_mutex_t * mutex;
public:    
	Aio(int sock, Buffer * buffer, pthread_mutex_t* mutex) : buffer(buffer), mutex(mutex) {
		aio = new aiocb;
		memset(aio, 0, sizeof(aio));
		aio->aio_fildes = sock;
		aio->aio_buf = buffer->buffer;
		aio->aio_nbytes = buffer->nbytes;

		struct sigaction sa;
		sa.sa_handler = (void (*)(int))bufferFinishCallback;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGIO, &sa, NULL);

		aio->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
		aio->aio_sigevent.sigev_signo  = SIGIO;
		aio->aio_sigevent.sigev_value.sival_ptr  = this;

	}

	Aio(int sock, char * buffer) {
		aio = new aiocb;
		memset(aio, 0, sizeof(aio));
		aio->aio_fildes = sock;
		aio->aio_buf = buffer;
		aio->aio_nbytes = strlen(buffer);

		struct sigaction sa;
		sa.sa_handler = (void (*)(int))liteFinishCallback;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGIO, &sa, NULL);

		aio->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
		aio->aio_sigevent.sigev_signo  = SIGIO;
		aio->aio_sigevent.sigev_value.sival_ptr  = this;
	}
	void write() {
		if (aio_write(aio)){
			if (buffer != NULL)
				buffer->free();
			close(aio->aio_fildes);
			delete this;
		}
	}

private:
	static void bufferFinishCallback(int sig, siginfo_t *info, void *context){
		Aio* item = (Aio *)info->si_value.sival_ptr;
		close(item->aio->aio_fildes);
		if (pthread_mutex_lock(item->mutex))
			quit(31, (char*)"ERROR lock buffers");
		if (item->buffer != NULL)
			item->buffer->free();
		if (pthread_mutex_unlock(item->mutex))
			quit(32, (char*)"ERROR unlock buffers");
		delete item;
	}
	static void liteFinishCallback(int sig, siginfo_t *info, void *context){
		Aio* item = (Aio *)info->si_value.sival_ptr;
		close(item->aio->aio_fildes);
		delete item;
	}
	

};
