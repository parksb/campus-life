import java.io.IOException;
import java.net.Socket;

public class SimpleTalkRequest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Socket	sock;
		try {
			sock = new Socket("127.0.0.1", 4242);
			System.out.println("networking established");
			new SimpleTalkClient(sock, "Talker A");
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

}
