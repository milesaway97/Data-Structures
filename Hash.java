import java.util.ArrayList;

public class Node {
    private String key;
    private Node next;
    public Node(String key){
        this.key = key;
        next = null;
    }
    public String getKey() {
        return key;
    }
    public void setNext(Node next){
        this.next = next;
    }
    public Node getNext(){
        return next;
    }
}

public class Node_LL {
    private ArrayList<String> list;
    public ArrayList<String> getList(){
        return list;
    }
    public void setList(ArrayList<String> list){
        this.list = list;
    }
}

public class SeparateChaining {
    private final int table_size = 50;
    private final Node_LL[] table;
    public SeparateChaining(){
        table = new Node_LL[table_size];
    }
    private int calcIndex(String word){
        return word.hashCode() % table_size;
    }
    private void insert(String word){
        int index = calcIndex(word);
        ArrayList<String> temp_list = table[index].getList();
        temp_list.add(0, word);
        table[index].setList(temp_list);
    }
    private boolean search(String word){
        int index = calcIndex(word);
        ArrayList<String> temp_list = table[index].getList();
        return temp_list.contains(word);
    }
    private boolean delete(String word){
        int index = calcIndex(word);
        ArrayList<String> temp_list = table[index].getList();
        if(temp_list.contains(word)){
            temp_list.remove(word);
            table[index].setList(temp_list);
            return true;
        }
        return false;
    }
}

public class CoalescedChaining {
    private final int table_size = 400;
    private final Node[] table;
    public CoalescedChaining(){
        table = new Node[table_size];
    }
    private int calcIndex(String word){
        return word.hashCode() % table_size;
    }
    private void insert(String word){
        int index = calcIndex(word);
        Node newCell = new Node(word);
        Node temp = table[index];
        newCell.setNext(temp);
        table[index] = newCell;
    }
    private boolean search(String word){
        int index = calcIndex(word);
        Node temp = table[index];
        while(temp != null){
            if(temp.getKey().equals(word)){
                return true;
            }
            temp = temp.getNext();
        }
        return false;
    }
    private boolean delete(String word){
        int index = calcIndex(word);
        Node temp = table[index];
        if(temp.getKey().equals(word)){
            table[index] = temp.getNext();
            temp.setNext(null);
            return true;
        }
        while(temp.getNext() != null){
            Node next = temp.getNext();
            if(next.getKey().equals(word)){
                temp.setNext(next.getNext());
                next.setNext(null);
                return true;
            }
            temp = temp.getNext();
        }
        return false;
    }
}
