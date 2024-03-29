import java.io.*;

public class ArquivoGrafo {
    private static Grafo grafo;

    public static void lerArquivo(String path) throws IOException {
        FileReader ler = new FileReader(path);
        BufferedReader reader = new BufferedReader(ler);

        String linha;
        int numVert = 0, numArc, v1, v2, peso;
        int cont = 0;
        while((linha = reader.readLine()) != null){
            if(cont == 0){
                numVert = Integer.parseInt(linha);
            }
            if(cont == 1){
                numArc = Integer.parseInt(linha);
                grafo = new Grafo(numVert, numArc);
            }
            if(cont > 1){
                v1 = Integer.parseInt(linha.split(" ", 3)[0]);
                v2 = Integer.parseInt(linha.split(" ", 3)[1]);
                peso = Integer.parseInt(linha.split(" ", 3)[2]);
                grafo.inserirArco(v1, v2, peso);
            }
            cont++;
        }
    }

    public static Grafo getGrafo(){
        return grafo;
    }
}
