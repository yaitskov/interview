package org.dan.ubs.problem1;

import lombok.SneakyThrows;

import java.io.BufferedReader;
import java.io.FileReader;

public class GraphLoader {
    private final String file;

    public GraphLoader(String file) {
        this.file = file;
    }

    @SneakyThrows
    public void load(MapGraph graph) {
        final FileReader in = new FileReader(file);
        try (BufferedReader br = new BufferedReader(in)) {
            int lineNumber = 0;
            while (true) {
                final String line = br.readLine();
                if (line == null) {
                    break;
                }
                ++lineNumber;
                if (line.matches(" *")) {
                    continue;
                }
                final int firstCommaIdx = line.indexOf(',');
                if (firstCommaIdx < 1) {
                    throw new RuntimeException("Line " + lineNumber + " is bad");
                }
                String c1 = line.substring(0, firstCommaIdx).trim();
                String c2 = line.substring(firstCommaIdx + 1).trim();
                if (c2.indexOf(',') >= 0) {
                    throw new RuntimeException("Line " + lineNumber + " has multiple commas");
                }
                graph.addConnection(c1, c2);
            }
        }
    }
}
