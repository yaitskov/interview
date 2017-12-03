package org.dan.ubs.problem1;

import java.util.List;
import java.util.Optional;

public class EntryPoint {
    public static void main(String[] args) {
        final String file = args[0];
        final String sourceCity = args[1];
        final String destinationCity = args[2];

        final MapGraph graph = new MapGraph();
        final DstAlgorithm algorithm  = new DstAlgorithm(graph);

        final GraphLoader graphLoader = new GraphLoader(file);
        graphLoader.load(graph);
        final Optional<List<String>> path = algorithm.find(sourceCity, destinationCity);
        if (path.isPresent()) {
            System.out.println("yes");
        } else {
            System.out.println("no");
        }
    }
}
