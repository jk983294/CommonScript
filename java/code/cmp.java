public class cmp {

    private Object1Comparator cmpor = new Object1Comparator();
    public void sortList(){
        Collections.sort(list, cmpor);
    }

    private class Object1Comparator implements Comparator<Object1> {
        @Override
        public int compare(Object1 o1, Object1 o2) {
            if(o1.getPerf() > o2.getPerf()) return 1;
            else if(o1.getPerf() < o2.getPerf()) return -1;
            else return 0;
        }
    }

}