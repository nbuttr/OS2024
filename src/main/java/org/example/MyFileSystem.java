package org.example;


import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.concurrent.Semaphore;


public class MyFileSystem implements FileSys {

    private static final int MAX_FILES = 1000;
    private static final int MAX_FILE_NAME = 32;
    private static final int MAX_DATA_SIZE = 1000;

    Map<String, String> files = new HashMap<>(MAX_FILES);
    private Semaphore semaphore = new Semaphore(1);


    @Override
    public void showInfo() {
        System.out.println("Числов файлов в системе:"+files.size());
    }

    @Override
    public void createFile(String fileName) {
        if(fileName.length()<MAX_FILE_NAME && !files.containsKey(fileName)){
            files.put(fileName,"");
            System.out.println("Файл успешно создан");
        }else{
            System.out.println("Имя файла превышает доступную длину или файл с таким названием существует");
        }

    }

    public void mainMethod(MyFileSystem fileSystem){
        System.out.println("Команды файловой системы: \n" +
                "rf -> Прочитать файл \n"+
                "cf -> Создать файл \n"+
                "wf -> Записать в файл \n"+
                "df -> Удалить файл \n"+
                "sf -> Поиск файла \n"+
                "si -> Показать информацию \n"+
                "end -> Выйти из файловой системы");
        Scanner sc = new Scanner(System.in);
        Boolean end = false;
        while(!end){
            String sw = sc.nextLine();
            switch(sw){
                case "rf":
                    System.out.println("Введите имя файла:");
                    String fileName = sc.nextLine();
                    fileSystem.readFile(fileName);
                    break;
                case "cf":
                    System.out.println("Введите имя файла:");
                    String fileName1 = sc.nextLine();
                    fileSystem.createFile(fileName1);
                    break;
                case "wf":
                    System.out.println("Введите имя файла:");
                    String fileName2 = sc.nextLine();
                    System.out.println("Введите текст:");
                    String fileChange = sc.nextLine();
                    fileSystem.writeFile(fileName2,fileChange);
                    break;
                case "df":
                    System.out.println("Введите имя файла, который надо удалить:");
                    String fileName3 = sc.nextLine();
                    fileSystem.deleteFile(fileName3);
                    break;
                case "sf":
                    System.out.println("Введите название файла или его содержимое:");
                    String fileName4 = sc.nextLine();
                    fileSystem.searchFile(fileName4);
                    break;
                case "si":
                    fileSystem.showInfo();
                    break;
                case "end":
                    end = true;

            }
        }


    }

    @Override
    public void readFile(String fileName) {
        try{
            semaphore.acquire();
        String fileContent = files.get(fileName);
        if(fileContent != null){
            System.out.println(files.get(fileName));
        }else{
            System.out.println("File is empty");
        }}catch (InterruptedException e){
            e.printStackTrace();
        }finally {
            semaphore.release();
        }
    }

    @Override
    public void writeFile(String fileName, String change) {
        if(change.length()<MAX_DATA_SIZE){
            try{
                semaphore.acquire();
                files.put(fileName,change);
            }catch (InterruptedException e){
                e.printStackTrace();

            }finally {
                semaphore.release();
            }
        }else{
            System.out.println("Слишком большой объем файла");
        }
    }

    @Override
    public void deleteFile(String fileName) {
        files.remove(fileName);
        System.out.println("Файл успешно удален");
    }

    @Override
    public void searchFile(String filenameOrFileContent) {
        if (files.containsKey(filenameOrFileContent)){
            System.out.println("Файл с таким названием есть в файловой системе");
        } else if (files.containsValue(filenameOrFileContent)) {
            System.out.println("Файл с таким содержанием есть в файловой системе");
        }else{
            System.out.println("Файла с таким названием и/или с таким содержанием нет в файловой системе");
        }
    }
}
