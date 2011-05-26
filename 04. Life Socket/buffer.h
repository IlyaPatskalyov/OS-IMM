class Buffer {
private:
	static unsigned int countFreeBuffers;
	unsigned int countClients;

	bool canGet(){
		return countClients > 0 || (countClients == 0 && countFreeBuffers > 2 );
	}

public:
	int nbytes;
	char buffer[2000];

	bool canUseForCalc(){
		return countClients == 0;
	}
	bool get(){
		if (!canGet())
			return false;
		if (countClients == 0){
			countFreeBuffers--;
		}
		countClients++;
		nbytes = 1641; // strlen(buffer);
		return true;
	}
	void free(){
		countClients--;
		if (countClients == 0){
			countFreeBuffers++;
		}
	}
};
