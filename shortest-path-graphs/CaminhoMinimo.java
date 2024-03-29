public abstract class CaminhoMinimo {
    protected static final int infinito = (int) Math.pow(2, 15) - 1;
    protected static int[] d, pi, Q;

    public static String printPath(int s, int v){
        String str = "";
        if(s == v){
            str += (s + 1);
        } else if(pi[v] == -1) {
            str += "Trajeto inexistente";
        } else {
            str += printPath(s, pi[v]);
            str += " -> " + (v + 1);
        }
        return str;
    }

    public static  void inicializaVets(int n, int s){
        pi = new int[n];
        d = new int[n];
        Q = new int[n];

        for (int i = 0; i < n; i++) {
            d[i] = infinito;
            pi[i] = -1;
        }
        d[s] = 0;
    }

    public static int[] getD() {
        return d;
    }

    public static int getInfinito() {
        return infinito;
    }
}