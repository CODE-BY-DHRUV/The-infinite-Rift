class Solution {
    int maxProduct(int[] arr) {
       int maxProduct = arr[0];
       int minProduct = arr[0];
       int answer = arr[0];
       
       for(int i = 1 ; i < arr.length;i++){
           int x = arr[i];
           
           if(x < 0){
               int temp = maxProduct;
               maxProduct = minProduct;
               minProduct = temp;
           }
           maxProduct = Math.max(x,maxProduct * x);
           minProduct = Math.min(x,minProduct * x);
           
           answer = Math.max(answer, maxProduct);
       }
       return answer;
        
    }
}