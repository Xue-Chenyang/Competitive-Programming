
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Stack;

class Solution {
    static class Scan {
        private byte[] buf = new byte[1024];
        private int index;
        private InputStream in;
        private long total;

        public Scan() {
            in = System.in;
        }

        public int scan() throws IOException {
            if (total < 0)
                throw new InputMismatchException();
            if (index >= total) {
                index = 0;
                total = in.read(buf);
                if (total <= 0)
                    return -1;
            }
            return buf[index++];
        }

        public int scanInt() throws IOException {
            int integer = 0;
            int n = scan();
            while (isWhiteSpace(n))
                n = scan();
            int neg = 1;
            if (n == '-') {
                neg = -1;
                n = scan();
            }
            while (!isWhiteSpace(n)) {
                if (n >= '0' && n <= '9') {
                    integer *= 10;
                    integer += n - '0';
                    n = scan();
                } else throw new InputMismatchException();
            }
            return neg * integer;
        }

        public long scanLong() throws IOException {
            long longeger = 0;
            long n = scan();
            while (isWhiteSpace(n))
                n = scan();
            long neg = 1;
            if (n == '-') {
                neg = -1;
                n = scan();
            }
            while (!isWhiteSpace(n)) {
                if (n >= '0' && n <= '9') {
                    longeger *= 10;
                    longeger += n - '0';
                    n = scan();
                } else throw new InputMismatchException();
            }
            return neg * longeger;
        }

        public double scanDouble() throws IOException {
            double doub = 0;
            long n = scan();
            while (isWhiteSpace(n))
                n = scan();
            long neg = 1;
            if (n == '-') {
                neg = -1;
                n = scan();
            }
            while (!isWhiteSpace(n) && n != '.') {
                if (n >= '0' && n <= '9') {
                    doub *= 10;
                    doub += n - '0';
                    n = scan();
                } else throw new InputMismatchException();
            }
            if (n == '.') {
                n = scan();
                double temp = 1;
                while (!isWhiteSpace(n)) {
                    if (n >= '0' && n <= '9') {
                        temp /= 10;
                        doub += (n - '0') * temp;
                        n = scan();
                    } else throw new InputMismatchException();
                }
            }
            return doub * neg;
        }

        public String scanString() throws IOException {
            StringBuilder sb = new StringBuilder();
            long n = scan();
            while (isWhiteSpace(n))
                n = scan();
            while (!isWhiteSpace(n)) {
                sb.append((char) n);
                n = scan();
            }
            return sb.toString();
        }

        private boolean isWhiteSpace(long n) {
            if (n == ' ' || n == '\n' || n == '\r' || n == '\t' || n == -1)
                return true;
            return false;
        }

        public String scanLine() throws IOException {
            StringBuilder sb = new StringBuilder();
            long n = scan();
            while (n != '\n' && n != -1 && n != '\r') {
                sb.append((char) n);
                n = scan();
            }
            if (n == '\r') {
                scan();
            }
            return sb.toString();
        }
    }

    static class Print {
        private final BufferedWriter bw;

        public Print() {
            this.bw = new BufferedWriter(new OutputStreamWriter(System.out));
        }

        public void print(Object object) throws IOException {
            bw.append("" + object);
        }

        public void println() throws IOException {
            bw.append("\n");
        }

        public void println(Object object) throws IOException {
            print(object);
            bw.append("\n");
        }

        public void close() {
            try {
                bw.close();
            } catch (IOException ex) {ex.printStackTrace();}
        }
    }

    static class Pair<U, V> {
        U key;
        V value;

        public Pair(U key, V value) {
            this.key = key;
            this.value = value;
        }

        public U getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }

        public void setKey(U key) {
            this.key = key;
        }

        public void setValue(V value) {
            this.value = value;
        }

        @Override
        public boolean equals(Object obj) {
            if (!(obj instanceof Pair)) {
                return false;
            }
            return ((Pair) obj).key.equals(this.key) && ((Pair) obj).value.equals(this.value);
        }

        @Override
        public String toString() {
            return key + " " + value;
        }

        @Override
        public int hashCode() {
            return key.hashCode() + value.hashCode();
        }
    }

    static Scan scan = new Scan();
    static Print print = new Print();
    static final int mod = 1000000007;

    public static void main(String[] args) {
        try {
            String string = scan.scanString();
            int[] inversion = new int[string.length() + 1];
            int[] ones = new int[string.length() + 1];
            int count = 1;
            for (int i = 0; i < string.length(); i ++) {
                if (string.charAt(i) == '1') {
                    inversion[i + 1] = inversion[i];
                    ones[i + 1] = (ones[i] + count) % mod;
                } else if (string.charAt(i) == '0') {
                    inversion[i + 1] = (inversion[i] + ones[i]) % mod;
                    ones[i + 1] = ones[i];
                } else {
                    inversion[i + 1] = ((inversion[i] + ones[i]) % mod + inversion[i]) % mod;
                    ones[i + 1] = ((2 * ones[i]) % mod + count) % mod;
                    count = (count << 1) % mod;
                }
            }
            print.println(inversion[string.length()]);
            print.close();
        } catch (InputMismatchException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}