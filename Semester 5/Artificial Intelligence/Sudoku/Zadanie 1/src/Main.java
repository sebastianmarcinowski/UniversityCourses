import java.util.*;

import sac.*;
import sac.examples.sudoku.Sudoku;
import sac.graph.BestFirstSearch;
import sac.graph.GraphSearchConfigurator;
import sac.graph.GraphState;
import sac.graph.GraphStateImpl;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

class SudokuState extends sac.graph.GraphStateImpl {
    private byte[][] sudoku;
    private int n;
    public SudokuState(int n){
        sudoku = new byte[n*n][n*n];
        this.n = n;
    }
    @Override
    public String toString(){
        StringBuilder s = new StringBuilder();
        for(byte[]r:sudoku){
            for(int i =0; i<r.length; i++){
                s.append(r[i]);
                //System.out.print(r[i]);
            }
        }
        return s.toString();
    }
    public void fromString(String s){
        sudoku = new byte[n*n][n*n];
        int id = 0;
        for(byte[]r:sudoku){
            for(int i =0; i<r.length; i++){
                if(s.charAt(i+id) != '.') r[i] = (byte)(s.charAt(i+id)-'0');
                //System.out.print(r[i]);
            }
            id = id+n*n;
        }
    }

    public boolean isValid(){
        //Sprawdzanie po kolumnach
        HashSet<Byte> kolumna =  new HashSet<Byte>();
        for(int i=0; i<n*n; i++){
            for(int j=0; j<n*n; j++){
                if(sudoku[j][i] != 0){
                    if(kolumna.contains(sudoku[j][i])) return false;
                    else{
                        kolumna.add(sudoku[j][i]);
                    }
                }
            }
            kolumna.clear();
        }
        //Sprawdzanie po wierszach
        HashSet<Byte> wiersz = new HashSet<Byte>();
        for(int i=0; i<n*n; i++){
            for(int j=0; j<n*n; j++){
                if(sudoku[i][j] != 0){
                    if(wiersz.contains(sudoku[i][j])) return false;
                    else{
                        wiersz.add(sudoku[i][j]);
                    }
                }
            }
            wiersz.clear();
        }
        //Sprawdzanie kwadratów
        HashSet<Byte> kwadrat = new HashSet<Byte>();
        for (int w=0; w<n*n; w+=n){
            for(int i=0; i<n*n; i+=n) {
                for (int j = w; j < w+n; j++) {
                    for (int k = i; k < i+n; k++) {
                        if(sudoku[j][k] != 0) {
                            if (kwadrat.contains(sudoku[j][k])) return false;
                            else kwadrat.add(sudoku[j][k]);
                        }
                    }
                }
                kwadrat.clear();
            }
        }
        return true;
    }
    public int ZeroCounter(){
        int counter = 0;

        for(int i=0; i<n*n; i++){
            for(int j=0; j<n*n; j++){
                if(sudoku[j][i] == 0) counter++;
            }
        }
        return counter;
    }


    @Override
    public int hashCode() {
        return toString().hashCode();
    }
    @Override
    public boolean isSolution() {
        return true;
    }
    @Override
    public List<GraphState> generateChildren(){
        int liczbaNiewiadomych = ZeroCounter();
        List<GraphState> children = new ArrayList<>();
        for(int i = 0; i<n*n; i++){
            for(int j = 0; j<n*n; j++){
                if(sudoku[i][j] == 0){
                    for(int k = 1; k<n*n; k++){
                        sudoku[i][j] = (byte)k;
                        liczbaNiewiadomych--;
                        if(isValid()) {
                            children.add(new SudokuState(sudoku[i][j]));
                            liczbaNiewiadomych++;
                            sudoku[i][j] = 0;
                        }
                    }
                    return children;
                }
            }
        }
        return children;
    }
}

class Heurustyka extends StateFunction{
    @Override
    public double calculate(State s){
        if (s instanceof SudokuState ){
            SudokuState ss = (SudokuState)s;
            return ss.ZeroCounter();
        }
        else{
            return Double.NaN;
        }
    }
}


public class Main {
    public static void main(String[] args) {
        /*String s = ".......................1...............................................2....3....";
        String s = ".....78....451.23.18..3...4...79........42..7.......1..1...4...79..2.3.8...87....";
        SudokuState sudoku = new SudokuState(3);
        sudoku.fromString(s);
        String temp = sudoku.toString();
        //System.out.print(temp);
        if(sudoku.isValid() == false){
            System.out.print("Nicht gut");
        }
        else {
            System.out.print("Gut");
        }
        //System.out.print(sudoku.ZeroCounter());
        */
        String s = "\" 8 , 5 , 4 , 2 , 1 , 9 , 7 , 6 , 3 , \" +\n" +
                 "3 , 9 , 7 , 8 , 6 , 5 , 4 , 2 , 1 , \" +\n" +
                "2 , 6 , 1 , 4 , 7 , 3 , 9 , 8 , 5 , \" +\n" +
                " 0 , 8 , 0 , 0 , 0 , 0 , 0 , 9 , 0 , \" +\n" +
                "6 \" 0 , 4 , 0 , 5 , 3 , 8 , 0 , 7 , 0 , \" +\n" +
                "7 \" 0 , 3 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , \" +\n" +
                "8 \" 9 , 2 , 6 , 3 , 8 , 4 , 5 , 1 , 7 , \" +\n" +
                "9 \" 5 , 0 , 3 , 7 , 0 , 0 , 0 , 4 , 8 , \" +\n" +
                "10 \" 4 , 7 , 8 , 0 , 0 , 1 , 0 , 0 , 0 \"";
        SudokuState sudoku = new SudokuState(3);
        sudoku.fromString(s);
        GraphSearchConfigurator gsc = new GraphSearchConfigurator();
        BestFirstSearch bfs = new BestFirstSearch(sudoku);
        bfs.execute();
        System.out.println( "SOLUTION: \n" + bfs.getSolutions());
    }
}