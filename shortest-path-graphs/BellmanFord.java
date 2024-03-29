public class BellmanFord extends CaminhoMinimo{

    public static void relaxa(int u, int v, int[][] mat){
        if(d[v] > d[u] + mat[u][v]){
            d[v] = d[u] + mat[u][v];
            pi[v] = u;
        }
    }

    public static boolean caminhosMinimos(Grafo G, int s) {
        int n = G.getNumVertices();
        int[][] mat = G.getMatAdj();

        boolean naoCiclico = true;
        inicializaVets(n, s);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if ( d[j] != infinito)
                        relaxa(j, k, mat);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i] != infinito && d[j] > d[i] + mat[i][j]) {
                    naoCiclico = false;
                    i = n;
                    j = n;
                }
            }
        }
        return naoCiclico;
    }
}
