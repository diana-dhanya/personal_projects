import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class korean_trie extends color_dictionary {
    public static void main(String[] args) throws IOException {
        color_dictionary korean_words = new color_dictionary();
        String[] koreanColors = {"빨간색", "주황색", "노란색", "초록색", "파란색", "보라색", "검은색", "하얀색", "갈색", "분홍색",
                "회색", "은색", "금색", "청동색"};
        Arrays.sort(koreanColors);
        System.out.println("정렬된 배열");
        for (String i : koreanColors) System.out.println(i);
        for (String i : koreanColors) korean_words.insert(i);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("색깔 단어 찾아보기: ");
        String search_color = br.readLine();
        if(korean_words.find(search_color))
            System.out.println(search_color + "은(는) 트라이에 있습니다.");
        else
            System.out.println(search_color + "은(는) 트라이에 없습니다.");
        String prefix = null;
        int results;
        try
        {
            System.out.print("접두사 입력하세요: ");
            prefix = br.readLine();
            System.out.print("반환할 결과수를 입력하세요: ");
            results = Integer.parseInt(br.readLine());
            int count = 0;
            //go through array once again
            for (String color : koreanColors) {
                assert prefix != null;
                if (color.startsWith(prefix))
                    count++;
            }
            System.out.println("접두사: " + prefix);
            System.out.println("이 접두사로 시작하는 결과수: " + count + "개");
            System.out.println("최고의 결과");
            System.out.println(korean_words.predict(prefix, results));
        }
        catch (IndexOutOfBoundsException exception)
        {
            System.out.println("배열 인덱스가 범위를 벗어났습니다.");
            System.out.println("최고의 결과를 반환할 수 없습니다. 다시 시도하십시오.");
            int count = 0;
            //go through array once again
            for (String color : koreanColors) {
                assert prefix != null;
                if (color.startsWith(prefix))
                    count++;
            }
            System.out.println("접두사: " + prefix);
            System.out.println("이 접두사로 시작하는 결과수: " + count + "개");
        }
    }
}
