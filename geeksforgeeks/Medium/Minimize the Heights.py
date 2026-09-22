import java.util.*;

class Solution{
    public int getMinDiff(int[] arr , int k){
        int n = arr.length;
        
        if(n <= 1){
            return 0;
        }
        Arrays.sort(arr);
        
        int ans = arr[n - 1] - arr[0];
        
        for(int i = 0; i < n-1;i++){
            int minHeight = Math.min(arr[0] + k,arr[i+1] - k);
            
            int maxHeight = Math.max(arr[i] + k , arr[n-1] - k);
            
            if(arr[i+1] - k < 0){
                continue;
            }
            ans = Math.min(ans,maxHeight - minHeight);
        }
        return ans;
        
    }
}

