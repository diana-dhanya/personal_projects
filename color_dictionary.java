import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class color_dictionary
{
    private static class color_node{
        public char value;
        public int count;
        public boolean isEnd;
        public HashMap<Character, color_node> children;
        color_node(char value)
        {
            this.value = value;
            this.count = 0;
            this.isEnd = false;
            this.children = new HashMap<>();
        }
    }
    private static class pair_up implements Comparable<pair_up>
    {
        public String s;
        public int count;
        public pair_up(String s, int count) {
            this.s = s; this.count = count;
        }
        public int compareTo(pair_up other_obj)
        {
            return Integer.compare(this.count, other_obj.count);
        }
    }
    public color_node root;
    public color_dictionary() {
        this.root = new color_node(' ');
    }
    public void insert(String s)
    {
        char[] word = s.toLowerCase().toCharArray();
        color_node current = root;
        for(char c : word) {
            if(!current.children.containsKey(c))
                current.children.put(c, new color_node(c));
            current = current.children.get(c);
        }
        current.isEnd = true;
        current.count+=1;
    }
    public boolean find(String s)
    {
        char[] word = s.toLowerCase().toCharArray();
        color_node current = root;
        for(char c: word) {
            if(current.children.containsKey(c))
                current = current.children.get(c);
            else
                return false;
        }
        return current.isEnd;
    }
    public List<String> predict(String s, int numberofwords)
    {
        char[] partial_word = s.toLowerCase().toCharArray();
        color_node current = root;
        for(char c : partial_word) {
            if(current.children.containsKey(c))
                current = current.children.get(c);
            else
                return new ArrayList<>();
        }
        List<pair_up> subtree_words = predict_helper(s, current);
        Collections.sort(subtree_words);
        List<String> top_words = new ArrayList<>();
        for(int i = 0; i < numberofwords; i++)
            top_words.add(subtree_words.get(i).s);
        return top_words;
    }
    private List<pair_up> predict_helper(String s, color_node current)
    {
        if(current.children.isEmpty())
            return Collections.singletonList(new pair_up(s, current.count));
        else
        {
            List<pair_up> current_words = new ArrayList<>();
            if(current.isEnd)
                current_words.add(new pair_up(s, current.count));
            for(Map.Entry entry: current.children.entrySet())
            {
                color_node searchNode = (color_node)entry.getValue();
                current_words.addAll(predict_helper(s + searchNode.value, searchNode));
            }
            return current_words;
        }
    }
    public static void main(String[] args) throws IOException {
        color_dictionary tree = new color_dictionary();
        String[] colors = {"white", "silver", "grey", "black", "navy", "blue", "cerulean", "sky-blue", "turquoise",
        "cyan", "azure", "teal", "yellow", "gold", "amber", "orange", "brown", "red", "maroon", "rose", "pink", "scarlet",
        "magenta", "purple", "indigo", "beige", "ivory", "lime", "lemon","peach", "green"};
        Arrays.sort(colors);
        System.out.println("Sorted Array.");
        for (String color : colors) System.out.println(color);
        for(String word: colors)
            tree.insert(word);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter a color to search for: ");
        String search_color = br.readLine();
        if(tree.find(search_color))
            System.out.println(search_color + " is in the trie.");
        else
            System.out.println(search_color + " is not in the trie.");
        String prefix = null;
        int results;
        try
        {
            System.out.print("Enter prefix: ");
            prefix = br.readLine();
            System.out.print("Enter number of results to return: ");
            results = Integer.parseInt(br.readLine());
            int count = 0;
            //go through array once again
            for (String color : colors) {
                assert prefix != null;
                if (color.startsWith(prefix))
                    count++;
            }
            System.out.println("Your prefix: " + prefix);
            System.out.println("Total number of words starting with your chosen prefix: " + count);
            System.out.println("Your Top Results");
            System.out.println(tree.predict(prefix, results));
        }
        catch(IndexOutOfBoundsException exception)
        {
            System.out.println("You went over the array boundaries.");
            System.out.println("Cannot return top words. Try again.");
            int count = 0;
            //go through array once again
            for (String color : colors) {
                assert prefix != null;
                if (color.startsWith(prefix))
                    count++;
            }
            System.out.println("Your prefix: " + prefix);
            System.out.println("Total number of words starting with your chosen prefix: " + count);
        }
        //Now let's switch over to Korean and do a different trie in Korean
    }
}