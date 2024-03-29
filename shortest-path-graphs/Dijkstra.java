public class Dijkstra extends CaminhoMinimo{

    public static void relaxa(int u, int v, int[][] mat){
        if(d[v] > d[u] + mat[u][v]){
            d[v] = d[u] + mat[u][v];
            pi[v] = u;
            Q[v] = d[v];
        }
    }

    public static int minimo(int n){
        int aux = infinito;
        int min = 0;
        for (int i = 0; i < n; i++) {
            if(Q[i] != -1 && Q[i] <= aux){
                aux = Q[i];
                min = i;
            }
        }
        return min;
    }

    public static void caminhosMinimos(Grafo G, int s){
        int n = G.getNumVertices();
        int[][] mat = G.getMatAdj();

        inicializaVets(n, s);

        Q = d.clone();

        for (int i = 1; i <= n; i++) {
            int u = minimo(n);
            for (int v = 0; v < n; v++) {
                if(mat[u][v] != infinito && mat[u][v] > 0){
                    relaxa(u, v, mat);
                }
            }
            Q[u] = -1;
        }
    }

}