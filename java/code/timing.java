public class timing {

    // measure execution time for a Java method
    public void doSomething() {
        long startTime = System.currentTimeMillis();
        doReallyLongThing();
        long endTime = System.currentTimeMillis();
        System.out.println("That took " + (endTime - startTime) + " milliseconds");
    }

    public void doSomething() {
        long t0 = System.nanoTime();
        doReallyLongThing();
        long t1 = System.nanoTime();
        long millis = TimeUnit.NANOSECONDS.toMillis(t1 - t0);
        System.out.println(String.format("sequential sort took: %d ms", millis));
    }

}