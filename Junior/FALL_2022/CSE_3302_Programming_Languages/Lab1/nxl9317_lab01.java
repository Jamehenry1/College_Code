// Nghia Lam
// 1001699317
// Windows 
// Using java 16.0.2

import java.io.File;

public class nxl9317_lab01 {
    public static void main(String[] args) 
    {

        File file = new File(".");
        int totalSize = calSize(file.listFiles()); //gets a list of files
        System.out.println(totalSize);
    }

    static int calSize(File[] allFiles)     
    {
        int size = 0;
        for(File fName: allFiles)                   //loop though the files
        {
            if(fName.isDirectory())                 //check if it is a directory
            {
                //System.out.println(fName);
                size += calSize(fName.listFiles()); //does recursion with the directory and adds the size

            }
            if(fName.isFile())                      //check if it is a file
            {
                //System.out.println(fName);
                size += fName.length();
                //System.out.println(size);
            }

        }
        return size;
    }

}