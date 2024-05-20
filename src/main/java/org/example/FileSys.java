package org.example;

public interface FileSys {
    public void showInfo();
    public void createFile(String fileName);
    public void readFile(String fileName);
    public void writeFile(String fileName,String change);
    public void deleteFile(String fileName);
    public void searchFile(String filenameOrFileContent);

}
