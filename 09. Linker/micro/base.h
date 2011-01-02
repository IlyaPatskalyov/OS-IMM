class Base {
public:
	static unsigned char inport(unsigned short port);
	static void outport(int port, unsigned char data);
};