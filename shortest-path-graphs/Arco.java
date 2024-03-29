public class Arco {
    private int v1;
    private int v2;
    private int peso;

    public Arco(int v1, int v2, int peso) {
        this.v1 = v1;
        this.v2 = v2;
        this.peso = peso;
    }

    public int getV1() {
        return v1;
    }

    public int getV2() {
        return v2;
    }

    public int getPeso() {
        return peso;
    }

    @Override
    public boolean equals(Object o){
        return this.v1 == ((Arco) o).getV1() && this.v2 == ((Arco) o).getV2() && this.peso == ((Arco) o).getPeso();
    }
}
