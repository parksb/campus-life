import java.io.IOException;
import java.net.Socket;

/**
 * 미디어 201700000 박성범
 * 변경사항: 1. client-server 통신 구현.
 *          2. draw mode: 클릭한 위치에 점을 생성.
 *          3. select mode: 점을 클릭해 선택하고 드래그하면 점 위치를 변경.
 */

public class EditorRequestTest {
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Socket sock;
        try {
            sock = new Socket("127.0.0.1", 4242);
            System.out.println("networking established");
            new EditorClient(sock, "Editor B");
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

}
