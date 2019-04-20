import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleTalkReceiver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			ServerSocket	serverSock = new ServerSocket(4242);
			Socket sock = serverSock.accept();
			System.out.println("networking established");
			new SimpleTalkClient(sock, "Talker B");
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

}
