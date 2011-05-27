const unsigned int POOL_SIZE = 1000;

class Pool
{
private:
	static unsigned int countFreeBuffers;
	static pthread_mutex_t poolLock;
	static void lock(){
		if (pthread_mutex_lock(&poolLock))
			quit(31, (char*)"ERROR lock pool");
	}
	static void unlock(){
		if (pthread_mutex_unlock(&poolLock))
			quit(32, (char*)"ERROR unlock pool");
	}
private:
	Buffer * queue[POOL_SIZE];
	Buffer * thisBuffer;
	int front, rear;
	
public:
	Pool(){
		front = 0;
		rear = POOL_SIZE - 1;
		for(int i = 0; i < POOL_SIZE; i++)
			queue[i] = new Buffer();
		thisBuffer = dequeueBuffer();
	}
	
	
	Buffer * getThisBuffer(){
		return thisBuffer;
	}
	void setThisBuffer(Buffer * buffer){
		lock();
		if (thisBuffer->countClients == 0)
			enqueueBuffer(thisBuffer);
		thisBuffer = buffer;
		unlock();
	}
	
	Buffer* attachClient(){
		lock();
		Buffer * result = NULL;
		if (thisBuffer->countClients > 0 || (thisBuffer->countClients == 0 && countFreeBuffers > 2 )){
			if (thisBuffer->countClients == 0)
				countFreeBuffers++;
			thisBuffer->countClients++;
			result = getThisBuffer();
		}
		unlock();
		return result;
	}
	
	void detachClient(Buffer * buffer){
		lock();
		buffer->countClients--;
		if (buffer->countClients == 0 && buffer != thisBuffer){
			countFreeBuffers++;
			enqueueBuffer(buffer);
		}
		unlock();
	}

	Buffer* initBuffer(){
		lock();
		Buffer * result = dequeueBuffer();
		unlock();
		return result;
	}

protected:
	void enqueueBuffer(Buffer * item){
		if ((rear+1)%POOL_SIZE == front)
			quit(41, (char*)"Pool is full");
		rear = (rear+1)%POOL_SIZE;
		queue[rear] = item;
		if (front == -1)
			front = 0;
	}
	Buffer * dequeueBuffer(){
		if (front == -1)
			quit(42, (char*)"Pool is empty");
		Buffer * result = queue[front];
		queue[front] = NULL;
		if (front == rear)
		{
			front = -1;
			rear = -1;
		}
		else
			front = (front+1) % POOL_SIZE;
		return result;
	}
};
