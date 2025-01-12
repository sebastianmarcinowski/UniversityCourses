import java.util.*;
import sac.*;
import sac.graph.*;
import sac.graph.AStar;

class Puzzle extends GraphStateImpl{
    private byte[][] board;
    private int size;
    private int emptyCellColumn;
    private int emptyCellRow;
    public Puzzle(int size){
        this.board = new byte[size][size];
        this.size = size;
        int id =0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = (byte)id;
                id++;
            }
        }
        this.emptyCellColumn = 0;
        this.emptyCellRow = 0;
    }
    public Puzzle(Puzzle parent){
        board = new byte[parent.size][parent.size];
        size = parent.size;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board[i][j] = parent.board[i][j];
            }
        }
        emptyCellColumn = parent.emptyCellColumn;
        emptyCellRow = parent.emptyCellRow;
    }
    @Override
    public String toString(){
        StringBuilder s = new StringBuilder();
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                s.append(board[i][j]);
            }
        }
        return s.toString();
    }

    @Override
    public boolean isSolution(){
        int id = 0;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j] != id){
                    return false;
                }
                id++;
            }
        }
        return true;
    }

    @Override
    public int hashCode(){
        return toString().hashCode();
    }

    @Override
    public List<GraphState> generateChildren(){
        List<GraphState> children = new ArrayList<>();
        String move;
        if(emptyCellRow != 0){
            move = "D";
            Puzzle child = new Puzzle(this);
            child.board[emptyCellRow][emptyCellColumn] = child.board[emptyCellRow-1][emptyCellColumn];
            child.board[emptyCellRow-1][emptyCellColumn] = 0;
            child.emptyCellRow -= 1;
            child.setMoveName(move);
            children.add(child);
        }
        if(emptyCellRow != size-1){
            move = "U";
            Puzzle child = new Puzzle(this);
            child.board[emptyCellRow][emptyCellColumn] = child.board[emptyCellRow+1][emptyCellColumn];
            child.board[emptyCellRow+1][emptyCellColumn] = 0;
            child.emptyCellRow += 1;
            child.setMoveName(move);
            children.add(child);
        }
        if(emptyCellColumn != 0){
            move = "R";
            Puzzle child = new Puzzle(this);
            child.board[emptyCellRow][emptyCellColumn] = child.board[emptyCellRow][emptyCellColumn-1];
            child.board[emptyCellRow][emptyCellColumn-1] = 0;
            child.emptyCellColumn -= 1;
            child.setMoveName(move);
            children.add(child);
        }
        if(emptyCellColumn != size-1){
            move = "L";
            Puzzle child = new Puzzle(this);
            child.board[emptyCellRow][emptyCellColumn] = child.board[emptyCellRow][emptyCellColumn+1];
            child.board[emptyCellRow][emptyCellColumn+1] = 0;
            child.emptyCellColumn += 1;
            child.setMoveName(move);
            children.add(child);
        }
        return children;
    }


    public int getMissplacedTilesValue(){
        int missplaced = 0;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j]/size != i || board[i][j]%size != j ){
                    if(board[i][j] != 0){
                        missplaced++;
                    }
                }
            }
        }
        return missplaced;
    }

    public int getManhattanValue(){
        int manhattan = 0;
        for (int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j] != 0){
                    if(board[i][j]/size != i || board[i][j]%size != j ) {
                        manhattan += Math.abs(i - (board[i][j] / size)) + Math.abs(j - (board[i][j] % size));
                    }
                }
            }
        }
        return manhattan;
    }

    public GraphState shuffle(int n){
        Random rand = new Random();
        GraphState newState = this;
        for(int i = 0; i < n; i++){
            List<GraphState> l = newState.generateChildren();
            newState = l.get(rand.nextInt(l.size()));
        }
        return newState;
    }

}

class HeurystykaManhattan extends StateFunction{
    @Override
    public double calculate(State s){
        if(s instanceof Puzzle){
            return ((Puzzle)s).getManhattanValue();
        }
        else{
            return Double.NaN;
        }
    }
}
class HeurystykaMissplacedTiles extends StateFunction{
    @Override
    public double calculate(State s){
        if(s instanceof Puzzle){
            return ((Puzzle)s).getMissplacedTilesValue();
        }
        else{
            return Double.NaN;
        }
    }
}

public class Main {
    public static void expand(int n, GraphState g){
        if(n<=0)System.out.println(g);
        else{
            for (GraphState t : g.generateChildren()){;
                expand(n-1,t);
            }
        }
    }

    public static void main(String[] args) {
        StateFunction[] heuristics = {new HeurystykaManhattan(), new HeurystykaMissplacedTiles()};
        Puzzle puzzle = new Puzzle(3);
            double[] openStatesSum = {0,0};
            double[] closedStatesSum = {0,0};
            double[] solveTimeSum = {0,0};
            double[] pathLengthSum = {0,0};
            GraphSearchAlgorithm algorithm = new AStar();
            for (int i=0; i<100; i++) {
                GraphState st = puzzle.shuffle(1000);
                for (StateFunction heuristic : heuristics) {
                    Puzzle.setHFunction(heuristic);
                    algorithm.setInitial(st);
                    algorithm.execute();
                    Puzzle solution = (Puzzle) algorithm.getSolutions().get(0);
                    if (heuristic instanceof HeurystykaManhattan) {
                        pathLengthSum[0] += solution.getPath().size();
                        openStatesSum[0] += algorithm.getOpenSet().size();
                        closedStatesSum[0] += algorithm.getClosedSet().size();
                        solveTimeSum[0] += algorithm.getDurationTime();
                    } else {
                        pathLengthSum[1] += solution.getPath().size();
                        openStatesSum[1] += algorithm.getOpenSet().size();
                        closedStatesSum[1] += algorithm.getClosedSet().size();
                        solveTimeSum[1] += algorithm.getDurationTime();
                    }
                }
            }
            System.out.println("Wyniki dla heurystyki Manhattan:");
            System.out.println("Srednia dlugosc sciezki: \n" + pathLengthSum[0]/100);
            System.out.println("Sredni czas wykonania[ms]: \n" + solveTimeSum[0]/100);
            System.out.println("Srednia liiczba stanow Closed: \n" + closedStatesSum[0]/100);
            System.out.println("Srednia liiczba stanow Open: \n" + openStatesSum[0]/100);
            System.out.println('\n');
            System.out.println("Wyniki dla heurystyki MissplacedTiles:");
            System.out.println("Srednia dlugosc sciezki: \n" + pathLengthSum[1]/100);
            System.out.println("Sredni czas wykonania[ms]: \n" + solveTimeSum[1]/100);
            System.out.println("Srednia liiczba stanow Closed: \n" + closedStatesSum[1]/100);
            System.out.println("Srednia liiczba stanow Open: \n" + openStatesSum[1]/100);
            System.out.println('\n');
    }
}