class Aio {
private:
	Buffer * buffer;
	aiocb * aio;
	Pool * pool;
public:    
	Aio(int sock, Pool * pool, Buffer * buffer) : buffer(buffer),  pool(pool) {
		aio = new aiocb;
		memset(aio, 0, sizeof(aio));
		aio->aio_fildes = sock;
		aio->aio_buf = buffer->buffer;
		aio->aio_nbytes = buffer->nbytes;

		setCallback((void (*))bufferFinishCallback);
		write();
	}

	Aio(int sock, char * buffer) {
		aio = new aiocb;
		memset(aio, 0, sizeof(aio));
		aio->aio_fildes = sock;
		aio->aio_buf = buffer;
		aio->aio_nbytes = strlen(buffer);

		setCallback((void (*))liteFinishCallback);
		write();
	}

private:
	void setCallback(void *callback ){
		struct sigaction sa;
		sa.sa_handler = (void (*)(int))callback;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGIO, &sa, NULL);

		aio->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
		aio->aio_sigevent.sigev_signo  = SIGIO;
		aio->aio_sigevent.sigev_value.sival_ptr  = this;
	}

	void write() {
		if (aio_write(aio)){
			fprintf(stderr, "write error");
			if (buffer != NULL)
				pool->detachClient(buffer);
			close(aio->aio_fildes);
			delete this;
		}
	}
	static void bufferFinishCallback(int sig, siginfo_t *info, void *context){
		Aio* item = (Aio *)info->si_value.sival_ptr;
		close(item->aio->aio_fildes);
		if (item->buffer != NULL)
			item->pool->detachClient(item->buffer);
		delete item;
	}
	static void liteFinishCallback(int sig, siginfo_t *info, void *context){
		Aio* item = (Aio *)info->si_value.sival_ptr;
		close(item->aio->aio_fildes);
		delete item;
	}
	
};
