package org.example;
import java.sql.*;
import java.util.Random;
//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) throws SQLException {
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/labs", "root", "");
            Statement stmt = conn.createStatement();
            stmt.execute("create table if not exists TabelaLab3 (id int PRIMARY KEY AUTO_INCREMENT, liczba int, napis text)");
            stmt.executeUpdate("delete from TabelaLab3");
            String[] tablica = {"Warszawa","Praga","Talinn","Ryga","Berlin","Lizbona","Madryt","Luksemburg","Kijow","Bratyslawa"};
            PreparedStatement pstmt = conn.prepareStatement("insert into TabelaLab3 (liczba,napis) values (?,?)");
            for (int i = 0; i <= 9; i++) {
                int liczba = new Random().nextInt();
                pstmt.setInt(1, liczba);
                pstmt.setString(2, tablica[i]);
                pstmt.executeUpdate();
            }
            ResultSet rs = stmt.executeQuery("select * from TabelaLab3");
            while (rs.next()) {
                System.out.println(rs.getString("napis") +"-"+rs.getInt("liczba"));
            }
        }
        catch (SQLException ex){
            System.out.print("Błąd Połaczenia \n");
            System.out.println(ex.getMessage());
        }
    }
}