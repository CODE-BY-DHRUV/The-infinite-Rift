class Solution{
    int maxCircularSum(int[] arr){
        int totalSum = 0;
        
        int maxEnding = arr[0];
        int maxSum = arr[0];
        
        int minEnding = arr[0];
        int minSum = arr[0];
        
        for(int i=0;i<arr.length;i++){
            totalSum += arr[i];
            
            if(i > 0){
                maxEnding = Math.max(arr[i],maxEnding + arr[i]);
                maxSum = Math.max(maxSum , maxEnding);
                
                minEnding = Math.min(arr[i],minEnding + arr[i]);
                minSum = Math.min(minSum,minEnding);
            }
        }
        if(maxSum < 0){
            return maxSum;
        }
        return Math.max(maxSum,totalSum - minSum);
        
    }
}