class Buffer {
public:
	Buffer () { 
		nbytes = 1641;
	}
	unsigned int countClients;
	int nbytes;
	char buffer[2000];
};
