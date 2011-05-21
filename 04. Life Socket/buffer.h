class Buffer {
private:
	static unsigned int countFreeBuffers;

public:
	int nbytes;
	unsigned int countClients;
	char buffer[2000];

	bool canGet(){
		return countClients > 0 || (countClients == 0 && countFreeBuffers > 2 );
	}
	
	void get(int sock){
		if (countClients == 0){
			countFreeBuffers--;
		}
		countClients++;
		nbytes = 1641; // strlen(buffer);
	}
	bool free(){
		countClients--;
		if (countClients == 0){
			countFreeBuffers++;
		}
	}
};
