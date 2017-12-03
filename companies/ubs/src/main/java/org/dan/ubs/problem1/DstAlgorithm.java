package org.dan.ubs.problem1;

import static java.util.Collections.emptyList;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Set;

public class DstAlgorithm {
    private final MapGraph graph;

    public DstAlgorithm(MapGraph graph) {
        this.graph = graph;
    }

    public Optional<List<String>> find(String src, String dst) {
        if (src.equals(dst)) {
            return Optional.of(emptyList());
        }
        ArrayList<String> visited = new ArrayList<>();
        visited.add(src);
        return find(src, dst, visited);
    }

    private Optional<List<String>> find(String current, String target, List<String> visited) {
        Set<String> l =  graph.connectedTo(current);
        if (l.contains(target)) {
            visited.add(target);
            return Optional.of(visited);
        }
        for (String neighbour : l) {
            if (visited.contains(neighbour)) {
                continue;
            }
            visited.add(neighbour);
            Optional<List<String>> r = find(neighbour, target, visited);
            if (r.isPresent()) {
                return r;
            }
            visited.remove(visited.size() - 1);
        }
        return Optional.empty();
    }
}
