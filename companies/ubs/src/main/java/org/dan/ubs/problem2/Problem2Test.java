package org.dan.ubs.problem2;

import java.util.Set;

public class Problem2Test {
    public <T> Set<T> intersect(Set<T> s1, Set<T> s2) {
        s1.retainAll(s2);
        s2.retainAll(s1);
        return s2;
    }
}
