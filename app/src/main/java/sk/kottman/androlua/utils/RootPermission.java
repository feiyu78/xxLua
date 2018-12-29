package sk.kottman.androlua.utils;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;

public class RootPermission {

    private static Process process;

    public static void rootPermission(String... command) {
        try {
            if(process == null)
                process = Runtime.getRuntime().exec("su");
            if (command != null && command.length > 0) {
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
                        process.getOutputStream()));
                for (int i = 0; i < command.length; i++) {
                    writer.write(command[i]);
                }
                writer.flush();
                writer.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
            process = null;
        }

    }
}
