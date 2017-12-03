package org.dan.ubs.problem1;

import static java.util.Collections.emptySet;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class MapGraph {
    private Map<String, Set<String>> edges = new HashMap<>();

    public void addConnection(String c1, String c2) {
        addDirection(c1, c2);
        addDirection(c2, c1);
    }

    private void addDirection(String c1, String c2) {
        Set<String> s1 = edges.get(c1);
        if (s1 == null) {
            s1 = new HashSet<>();
            edges.put(c1, s1);
        }
        s1.add(c2);
    }

    public Set<String> connectedTo(String c) {
        return  edges.getOrDefault(c, emptySet());
    }
}
