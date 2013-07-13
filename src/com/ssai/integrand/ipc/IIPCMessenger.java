package com.ssai.integrand.ipc;

import java.io.IOException;

public interface IIPCMessenger {
	boolean open();
	void close();
	void readFifoMessage(byte[] messageBuffer, int size) throws IOException;
	void writeMessege(byte[] messageBuffer, int size) throws IOException;
}
