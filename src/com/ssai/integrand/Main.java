package com.ssai.integrand;

import java.io.IOException;
import java.nio.ByteBuffer;

import com.ssai.integrand.ipc.FifoIPCMessenger;
import com.ssai.integrand.ipc.IIPCMessenger;


public class Main {
	private static final String INPUT_FIFO = "/tmp/fromCppToJava";
	private static final String OUTPUT_FIFO = "/tmp/fromJavaToCpp";

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("Starting integrated process. To exit press Ctrl+C.");
		
		// open pipes
		FifoIPCMessenger messenger = new FifoIPCMessenger(INPUT_FIFO, OUTPUT_FIFO);
		if (!messenger.open()) {
			System.out.println("Can't open pipes");
			return;
		}

		mainLoop(messenger);
		//echoTestLoop(messenger);
		
		messenger.close();
		System.out.println("Exiting...");
	}
	
	private static void mainLoop(IIPCMessenger messenger) {
		byte[] messegeLength = new byte[FifoIPCMessenger.MESSAGE_LENGTH_SIZE];
		byte[] returnMessege = new byte[FifoIPCMessenger.MESSAGE_LENGTH_SIZE * 2];
		while (true) {
			try {
				// read dim
				messenger.readFifoMessage(messegeLength, FifoIPCMessenger.MESSAGE_LENGTH_SIZE);
				long startTime = System.currentTimeMillis(); // profiling
				int dim = (int) byteToDouble(messegeLength);
				
				// read params
				byte[] messenge = new byte[dim * FifoIPCMessenger.MESSAGE_LENGTH_SIZE];
				messenger.readFifoMessage(messenge, dim * FifoIPCMessenger.MESSAGE_LENGTH_SIZE);			
				ByteBuffer doubles = ByteBuffer.wrap(messenge);
				
				// calculate and create response message
				double result = integrated(doubles, dim);
				ByteBuffer returnArray = ByteBuffer.wrap(returnMessege);
				returnArray.putDouble(result);
				long endTime = System.currentTimeMillis(); // profiling
				returnArray.putDouble((double)(endTime - startTime)); // profiling
				
				// write message
				//System.out.println("Result = " + result);
				messenger.writeMessege(returnMessege, FifoIPCMessenger.MESSAGE_LENGTH_SIZE * 2);
			} catch (IOException e) {
			}
		}
	}
	
	@SuppressWarnings("unused")
	private static void echoTestLoop(IIPCMessenger messenger) {
		byte[] messegeLength = new byte[FifoIPCMessenger.MESSAGE_LENGTH_SIZE];
		while (true) {
			try {
				// read dim
				messenger.readFifoMessage(messegeLength, FifoIPCMessenger.MESSAGE_LENGTH_SIZE);
				double result = byteToDouble(messegeLength);
				System.out.println("Get double = " + result);
				// read params
				byte[] messenge = new byte[FifoIPCMessenger.MESSAGE_LENGTH_SIZE];			
				ByteBuffer doubles = ByteBuffer.wrap(messenge);
				doubles.putDouble(result);
				// write message
				messenger.writeMessege(messenge, FifoIPCMessenger.MESSAGE_LENGTH_SIZE);
				System.out.println("Sended double = " + result);
			} catch (IOException e) {
			}
		}
	}

	private static double byteToDouble(byte[] b) {
		ByteBuffer i = ByteBuffer.wrap(b);
		return i.getDouble();
	}

	private static double integrated(ByteBuffer doubles, int size) {
		double[] args = new double[size];
		for (int i = 0; i < size; ++i) {
			args[i] = doubles.getDouble();
		}
		return integrated(args);
	}
	
	private static double integrated(double[] args) {
		double sum = 0.0;
		for (double x : args) {
			sum += x;
		}
		return Math.sin(sum);
	}

}
