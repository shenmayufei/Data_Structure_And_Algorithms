## 顺序栈的Java实现

JDK包中也提供了"栈"的实现，它就是集合框架中的Stack类。本部分给出2种Java实现

###  栈的数组实现

数组实现的栈，能存储任意类型的数据

```java
// Java : 数组实现的栈，能存储任意类型的数据
import java.lang.reflect.Array;

public class GeneralArrayStack<T> {

    private static final int DEFAULT_SIZE = 12;
    private T[] mArray;
    private int count;

    public GeneralArrayStack(Class<T> type) {
        this(type, DEFAULT_SIZE);
    }

    public GeneralArrayStack(Class<T> type, int size) {
        // 不能直接使用mArray = new T[DEFAULT_SIZE];
        mArray = (T[]) Array.newInstance(type, size);
        count = 0;
    }

    // 将val添加到栈中
    public void push(T val) {
        mArray[count++] = val;
    }

    // 返回“栈顶元素值”
    public T peek() {
        return mArray[count-1];
    }

    // 返回“栈顶元素值”，并删除“栈顶元素”
    public T pop() {
        T ret = mArray[count-1];
        count--;
        return ret;
    }

    // 返回“栈”的大小
    public int size() {
        return count;
    }

    // 返回“栈”是否为空
    public boolean isEmpty() {
        return size()==0;
    }

    // 打印“栈”
    public void PrintArrayStack() {
        if (isEmpty()) {
            System.out.printf("stack is Empty\n");
        }

        System.out.printf("stack size()=%d\n", size());

        int i=size()-1;
        while (i>=0) {
            System.out.println(mArray[i]);
            i--;
        }
    }

    public static void main(String[] args) {
        String tmp;
        GeneralArrayStack<String> astack = 
          new GeneralArrayStack<String>(String.class);

        // 将10, 20, 30 依次推入栈中
        astack.push("10");
        astack.push("20");
        astack.push("30");

        // 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
        tmp = astack.pop();
        System.out.println("tmp="+tmp);

        // 只将“栈顶”赋值给tmp，不删除该元素.
        tmp = astack.peek();
        System.out.println("tmp="+tmp);

        astack.push("40");
        astack.PrintArrayStack();    // 打印栈
    }
}
```

运行结果：

```
tmp=30
tmp=20
stack size()=3
40
20
10
```
结果说明：GeneralArrayStack是通过数组实现的栈，而且GeneralArrayStack中使用到了泛型

### 集合框架中的Stack

Java的 Collection 集合中自带的"栈"(stack)的示例

```java
import java.util.Stack;

// Java : java集合包中的Stack的演示程序
public class StackTest {

    public static void main(String[] args) {
        int tmp=0;
        Stack<Integer> astack = new Stack<Integer>();

        // 将10, 20, 30 依次推入栈中
        astack.push(10);
        astack.push(20);
        astack.push(30);

        // 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
        tmp = astack.pop();
        //System.out.printf("tmp=%d\n", tmp);

        // 只将“栈顶”赋值给tmp，不删除该元素.
        tmp = (int)astack.peek();
        //System.out.printf("tmp=%d\n", tmp);

        astack.push(40);
        while(!astack.empty()) {
            tmp = (int)astack.pop();
            System.out.printf("tmp=%d\n", tmp);
        }
    }
}
```
运行结果：

```
tmp=40
tmp=20
tmp=10
```