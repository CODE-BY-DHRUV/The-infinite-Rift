


public int[] resolveAsteroidCollisions(int[] asteroidList) {

    java.util.Stack<Integer> st = new java.util.Stack<>();

    for (int asteroid : asteroidList) {

        boolean destroyed = false;

        while (!st.isEmpty() && asteroid < 0 && st.peek() > 0) {

            if (st.peek() < -asteroid) {
                st.pop();
            }
            else if (st.peek() == -asteroid) {
                st.pop();
                destroyed = true;
                break;
            }
            else {
                destroyed = true;
                break;
            }
        }

        if (!destroyed) {
            st.push(asteroid);
        }
    }

    int[] result = new int[st.size()];

    for (int i = 0; i < st.size(); i++) {
        result[i] = st.get(i);
    }

    return result;
}

