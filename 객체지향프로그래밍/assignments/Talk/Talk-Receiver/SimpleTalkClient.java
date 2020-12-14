import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class SimpleTalkClient {
	JTextField outgoing;
	JTextField incoming;
	PrintWriter writer;
	BufferedReader	reader;
	Socket sock;
	
	public SimpleTalkClient(Socket s, String name) {
		String msg;

		setUpNetworking(s);
		go(name);

		// Create and start a thread to receive messages from the other user.
		while(true) {
			try {
				msg = reader.readLine();
				incoming.setText(msg);
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}

	}

	public void go(String name) {
		JFrame frame = new JFrame(name);
		JPanel mainPanel = new JPanel();
		outgoing = new JTextField(20);	
		incoming = new JTextField(20);	
		JButton sendButton = new JButton("Send");
		sendButton.addActionListener(new SendButtonListener());
		mainPanel.add(outgoing);
		mainPanel.add(sendButton);
		frame.getContentPane().add(BorderLayout.CENTER, mainPanel);
		frame.getContentPane().add(BorderLayout.NORTH, incoming);
		frame.setSize(400,500);
		frame.setVisible(true);
		outgoing.requestFocus();
	}

	
	private boolean setUpNetworking(Socket s) {
		try {
			sock = s;
			// Make PrintWriter and BufferedReader objects with s
			reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			writer = new PrintWriter(sock.getOutputStream());
		} catch (IOException ex) {
			ex.printStackTrace();
			return false;
		}
		return true;
	}
	
	public class SendButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			String	text = outgoing.getText();
			try {
				// Write code to send the text to the other user
				writer.println(text);
				writer.flush();
			} catch (Exception ex) {
				ex.printStackTrace();
			}
			outgoing.setText("");
			outgoing.requestFocus();
		}
	}
	
}
