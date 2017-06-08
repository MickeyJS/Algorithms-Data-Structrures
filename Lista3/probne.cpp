

    void sort(int start, int end) {
        if (start < end) {
            int pivot = partition(start, end);

            sort(start, pivot-1);
            sort(pivot+1, end);
        }
    }

    private int select(int start, int end, int i) {
        if (start == end)
            return start;
        int pivot = 0;
        while(true) {
            pivot = partition(start, end);

            if (i-1 == pivot)
                return pivot;
            else
            if (i-1 < pivot)
                end = pivot - 1;
            else
                start = pivot + 1;
        }
    }

    private int partition(int start, int end) {
        int pivot = selectPivot(start, end);
        int pivotValue = data.get(pivot);

        swap(pivot, end);

        int index = start;
        for (int i=start; i<end; i++) {
            if (compare(data.get(i), pivotValue) < 0) {
                swap(i, index);
                index++;
            }
        }
        swap(index, end);

        return index;
    }

    protected int selectPivot(int start, int end){
        // IF PART HAVE 5 OR LESS ELEMENTS RETURN MEDIAN OF THEM
        if (end - start < 5) {
            return median(start, end);
        }
        // ELSE GET MEDIANS OF ALL THE 5-THS AND MOVE THEM TO LIST BEGINNING
        // ITERATE FROM START TO END BY 5 INDEXES
        for (int i=start; i<=end; i+=5) {
            // SUBEND IS 4 ELEMENTS FURTHER THAN START
            int end2 = i + 4;
            // IF LAST SUBGROUP EXTENDS BEYOND LIST SIZE
            // CHANGE SUBEND TO LIST END
            if (end2 > end)
                end2 = end;
            // GET MEDIAN OF 5-TH
            int median5 = median(i, end2);
            // MOVE MEDIAN OF 5-TH TO BEGGINING AT INDEX CORRESPONDING
            // TO THAT 5-TH INDEX IN ALL 5-THS
            swap(median5, (start + (int) Math.floor((i - start) / 5)));
        }
        // CALL SELECT ON ALL MEDIANS TO GET MEDIAN OF THE MEDIANS
        // START IS START, END IN CALCULETED BY NUMBER OF 5-THS IN LIST
        // AS THERE ARE THAT MUCH MEDIANS ON THE BEGGINING OF THE LIST NOW
        // AND WE ARE LOOKING FOR MEDIAN OF MEDIANS SO CALLING SELECT
        // LOOKING FOR K-TH ELEMENT WHERE K IS HALF OF ALL MEDIANS
        return select(start, start + (int) Math.ceil((end - start) / 5), (int) Math.floor(start + (end - start) / 10) + 1);
    }

    private int median(int start, int end) {
        // SIMPLE INSERT SORT IMPLEMENTATION TO GET MEDIAN OF 5 OR LESS ELEMENTS
        int j;
        for(int i=start+1; i<=end; i++) {
            j = i-1;

            while(j>=start && compare(data.get(j), data.get(j+1))>0) {
                swap(j+1, j);
                j--;
            }
        }
        return ((int) Math.floor((end + start) / 2));
}
