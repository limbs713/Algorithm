import java.io.*;
import java.util.*;

public class Main {
    static char[][] arr = new char[3000][3000];
    
    public static void print_star(int x0, int x1, int y0, int y1) {
        // 탈출 조건
        if (x0 == x1 - 1 && y0 == y1 - 1) {
            arr[x0][y0] = '*';
            return;
        }
        
        // 분할 정복
        // 첫번째 부분 3개로 쪼개서 정사각형 찍어라
        int first_x = (x1 - x0) / 3;
        int first_y = (y1 - y0) / 3;
        print_star(x0, first_x + x0, y0, first_y + y0);
        print_star(x0, first_x + x0, first_y + y0, first_y * 2 + y0);
        print_star(x0, first_x + x0, first_y * 2 + y0, y1);
        
        // 두번째 부분 3개로 쪼개서 가운데는 공백, 나머지는 정사각형 찍어라
        print_star(first_x + x0, first_x * 2 + x0, y0, first_y + y0);
        // 가운데는 안 찍음
        print_star(first_x + x0, first_x * 2 + x0, first_y * 2 + y0, y1);
        
        // 세번째 부분 3개로 쪼개서 정사각형 찍어라
        print_star(first_x * 2 + x0, x1, y0, first_y + y0);
        print_star(first_x * 2 + x0, x1, first_y + y0, first_y * 2 + y0);
        print_star(first_x * 2 + x0, x1, first_y * 2 + y0, y1);
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        
        // 배열 초기화 (공백으로)
        for (int i = 0; i < 3000; i++) {
            Arrays.fill(arr[i], ' ');
        }
        
        int n = Integer.parseInt(br.readLine());
        print_star(0, n, 0, n);
        
        // 결과 출력
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bw.write(arr[i][j]);
            }
            bw.write('\n');
        }
        
        bw.flush();
        bw.close();
        br.close();
    }
}