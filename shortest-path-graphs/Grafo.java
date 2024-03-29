import java.util.ArrayList;
public class Grafo {
    private int numVertices;
    private int numArcos;
    private ArrayList<Arco> arcos;
    private ArrayList<Integer> vertices;
    private int[][] matInc;
    private int[][] matAdj;

    public Grafo(int numVertices, int numArcos) {
        this.numVertices = numVertices;
        this.numArcos = numArcos;
        matInc = new int[numVertices][numArcos];
        matAdj = new int[numVertices][numVertices];
        arcos = new ArrayList<>();
        vertices = new ArrayList<>();
    }



    public void inserirVertice(int vert){
        if(!vertices.contains(vert)){
            vertices.add(vert);
        }
    }

    public void inserirArco(int v1, int v2, int peso){
        inserirVertice(v1);
        inserirVertice(v2);
        Arco novoArco = new Arco(v1, v2, peso);
        for(Arco arco : arcos){
            if(arco.equals(novoArco)){
                return;
            }
        }
        arcos.add(novoArco);
        atualizaMatInc(v1, v2);
        atualizaMatAdj();
    }

    public void initMatInc(){
        for(int i = 0; i < numVertices; i++){
            for (int j = 0; j < numArcos; j++) {
                matInc[i][j] = 0;
            }
        }
    }

    public void atualizaMatInc(int v1, int v2){
        int a = 0, b = 0, contArc = 0;
        for(Arco arc : arcos){
            if(arc.getV1() == v1 && arc.getV2() == v2){
                break;
            }
            contArc++;
        }
        int cont = 0;
        for(int v : vertices){
            if(v == v1){
                a = cont;
            }
            if(v == v2){
                b = cont;
            }
            cont++;
        }
        matInc[a][contArc] = -1;
        matInc[b][contArc] = 1;
    }

    public String exibirMatInc(){
        String s = "";
        for (int i = 0; i < numArcos; i++) {
            s += "\t" + arcos.get(i).getV1() + "->" + arcos.get(i).getV2();
        }
        s += "\n";
        for (int i = 0; i < numVertices; i++) {
            s += vertices.get(i) + ":";
            for (int j = 0; j < numArcos; j++) {
                if(matInc[i][j] == -1){
                    s += " " + matInc[i][j];
                } else {
                    s += "  " + matInc[i][j];
                }
                s += "     ";
            }
            s += "\n";
        }
        return s;
    }

    public void initMatAdj(){
        for(int i = 0; i < numVertices; i++){
            for (int j = 0; j < numVertices; j++) {
                matAdj[i][j] = Dijkstra.getInfinito();
            }
        }
    }

    public void atualizaMatAdj(){
        int a = 0, b = 0;
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices.size(); j++) {
                for(Arco arc : arcos) {
                    a = arc.getV1() == vertices.get(i) ? i : -1;
                    b = arc.getV2() == vertices.get(j) ? j : -1;
                    if (a != -1 && b != -1) {
                        matAdj[a][b] = arc.getPeso();
                    }
                }
            }
        }
    }

    public String exibirMatAdj(){
        String s = "    ";
        for (int i = 0; i < numVertices; i++) {
            s += vertices.get(i) + "       ";
        }
        s += "\n";
        for (int i = 0; i < numVertices; i++) {
            s += vertices.get(i) + ":";
            for (int j = 0; j < numVertices; j++) {
                if(matAdj[i][j] == Dijkstra.getInfinito()){
                    s += " " + " ∞";
                } else if(matAdj[i][j] > 9) {
                    s += " " + matAdj[i][j];
                } else {
                        s += "  " + matAdj[i][j];
                }
                s += "     ";
            }
            s += "\n";
        }
        return s;
    }

    public int getNumVertices() {
        return numVertices;
    }

    public void setNumVertices(int numVertices) {
        this.numVertices = numVertices;
    }

    public int getNumArcos() {
        return numArcos;
    }

    public void setNumArcos(int numArcos) {
        this.numArcos = numArcos;
    }

    public ArrayList<Arco> getArcos() {
        return arcos;
    }

    public void setArcos(ArrayList<Arco> arcos) {
        this.arcos = arcos;
    }

    public ArrayList<Integer> getVertices() {
        return vertices;
    }

    public void setVertices(ArrayList<Integer> vertices) {
        this.vertices = vertices;
    }

    public int[][] getMatInc() {
        return matInc;
    }

    public void setMatInc(int[][] matInc) {
        this.matInc = matInc;
    }

    public int[][] getMatAdj() {
        return matAdj;
    }

    public void setMatAdj(int[][] matAdj) {
        this.matAdj = matAdj;
    }
}
