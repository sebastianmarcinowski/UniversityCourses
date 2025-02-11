import java.sql.*;

public class Zadanie4 {
    public static void main(String[] args) throws SQLException{
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/labs","root","");
        Statement stmt = conn.createStatement();

        stmt.execute("create table if not exists tabela (id int PRIMARY KEY AUTO_INCREMENT, liczba int, napis text");
        stmt.executeUpdate("insert into tabela (liczba, napis) values(1,'abc')");
        ResultSet rs = stmt.executeQuery("select * from tabela");

        while(rs.next()){
            int liczba = rs.getInt("liczba");
            String napis = rs.getString("napis");
            System.out.println(liczba + " " + napis);
        }
    }
}