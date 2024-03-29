import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        ArquivoGrafo.lerArquivo("src/grafo.txt");
        Grafo grafo = ArquivoGrafo.getGrafo();

        System.out.println("***Matriz de Incidência do Grafo***");
        System.out.println(grafo.exibirMatInc());
        System.out.println("***Matriz de Adjacência do Grafo***");
        System.out.println(grafo.exibirMatAdj());

        Grafo grafoAux = grafo;

        System.out.print("Caminhos mínimos com algoritmo de Dijkstra");
        for (int s = 0; s < grafo.getNumVertices(); s++) {
            Dijkstra.caminhosMinimos(grafo, s);
            System.out.println("");
            for (int i = 0; i < grafo.getNumVertices(); i++) {
                String x = Dijkstra.getD()[i] > 9 ? " " : "  ";
                System.out.print("De " + (s + 1) + " para " + (i + 1) + " [Peso: " + x + Dijkstra.getD()[i] + "]:   ");
                System.out.println(Dijkstra.printPath(s, i));
            }
        }

        System.out.println("\n");

        System.out.print("Caminhos mínimos com algoritmo de Bellman-Ford");
        for (int s = 0; s < grafoAux.getNumVertices(); s++) {
            boolean t = BellmanFord.caminhosMinimos(grafoAux, s);
            int d[] =  BellmanFord.getD();
            System.out.println("");
                if(t){
                    for (int i = 0; i < grafoAux.getNumVertices(); i++) {
                        String x = d[i] > 9 ? " " : "  ";
                        System.out.print("De " + (s + 1) + " para " + (i + 1) + " [Peso: " + x + d[i] + "]:   ");
                        System.out.println(BellmanFord.printPath(s, i));
                    }
                } else {
                    System.out.println("Nao ha solucoes possiveis");
                }
        }

    }
}