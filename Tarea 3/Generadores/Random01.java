import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Random01 {

    public static void main(String[] args) {
        final int CANTIDAD = 1_000_000;
        Random random = new Random();

        try (BufferedWriter writer = new BufferedWriter(
                new FileWriter("randomJava_0_1.txt"))) {

            for (int i = 0; i < CANTIDAD; i++) {
                double valor = random.nextDouble(); // [0,1)
                writer.write(Double.toString(valor));
                writer.newLine();
            }

            System.out.println("Archivo generado correctamente.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
