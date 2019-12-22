/*
 Note:
 - Change the changeSpeed function
 - Change userColor
 */


package application;

import java.io.*;
import java.lang.*;
import java.util.*;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.*;
import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.scene.transform.Rotate;
import javafx.scene.shape.*;
import javafx.scene.paint.*;
import javafx.geometry.*;

public class OS141 extends Application{
	public static int NUM_USERS = 4;
	public static int NUM_DISKS = 2;
	public static int NUM_PRINTERS = 3;
	public static String userFileNames[];
	public static UserThread Users[];
	static Disk disks[];
	static Printer printers[];
	static DiskManager diskManager;
	static DiskManager.DirectoryManager DirectoryManager;
	static PrinterManager PrinterResource;
	public static boolean ngFlag = false;
	
	//GUI member variables
	Stage primaryStage;
	public static GridPane gridpane = new GridPane();
	public static GridPane diskPane = new GridPane();
	public static GridPane userPane = new GridPane();
	public static GridPane printerPane = new GridPane();
	Text welcomeText;
	public static String[] UserColor = {"#fe8f43","#ffd700","#00ff00","#ff00f4"};
	
	//Set up speed button	
	Button speedButton;
	public static int currentSpeed = 1;
	public static double speedOptions[] = {.5,1,2,4};
	public static String speedChoices[] = {"Double\nSpeed","Normal\nSpeed","Half\nSpeed","Quarter\nSpeed"};	
	
	//Set up List view of Printers	
	public static ObservableList<String> observList1 = FXCollections.observableArrayList();
	public static ObservableList<String> observList2 = FXCollections.observableArrayList();
	public static ObservableList<String> observList3 = FXCollections.observableArrayList();
	
	static ListView<String> listView1 = new ListView();
	static ListView<String> listView2 = new ListView();
	static ListView<String> listView3 = new ListView();
	
	public static Rectangle printer1Rec = new Rectangle();
	public static Rectangle printer2Rec = new Rectangle();
	public static Rectangle printer3Rec = new Rectangle();
	
	public static Text printer1;
	public static Text printer2;
	public static Text printer3;	
	
	public static void main (String args[]) throws IOException,InterruptedException {
		for(String arg : args)
		{
			if(arg.equals("-ng")) {
				ngFlag = true;
			}
		}
		if(ngFlag) {
			OSSetup();
		}
		else {
			launch(args);
		}
				
	}
	void configure(String args[]) {
		this.NUM_USERS = Integer.parseInt(args[0])*(-1);
		System.out.println("No of Users: " + NUM_USERS);
		int argsCount = 1;
		userFileNames = new String[NUM_USERS];
		for (int i = 1; i <= NUM_USERS; i++) {
			userFileNames[i-1] = args[i];
		}
		this.NUM_DISKS = Integer.parseInt(args[argsCount + NUM_USERS])*(-1);
		System.out.println("No of Disks: " + NUM_DISKS);
		this.NUM_PRINTERS = Integer.parseInt(args[argsCount + NUM_USERS + 1])*(-1);
		System.out.println("No of Printers: " + NUM_PRINTERS);
		
	}
	
	public static void OSSetup(){
		//configure(args);
		userFileNames = new String[NUM_USERS];
		for (int i = 1; i <= NUM_USERS; i++) {
			userFileNames[i-1] = "USER"+i;
		}
		
		diskManager = new DiskManager(NUM_DISKS);
		DirectoryManager = diskManager.new DirectoryManager();
		
		//Read number of Users			
		Users = new UserThread[NUM_USERS];			
		
		//Get number of Disks		
		disks = new Disk[NUM_DISKS];
		//Set up Disk
		for (int i = 0; i < NUM_DISKS; i++) {
			disks[i] = new Disk(i+1);
		}		
		
		//Get number of Printers		
		PrinterResource = new PrinterManager(NUM_PRINTERS);
		printers = new Printer[NUM_PRINTERS];
		//Set up Printers
		for (int i = 0; i < NUM_PRINTERS; i++) {
			printers[i] = new Printer(i+1);
		}		
		
		//Set up UserThread
		for(int i = 1; i <= NUM_USERS; i++)
		{
			File file = new File("./inputs/" + userFileNames[i-1]);
			UserThread user = new UserThread(i,file);
			Users[i-1] = user;				
		}
		//Start UserThread
		for (int i = 0; i < NUM_USERS; i++) {
			Users[i].start();
		}	
	}
	
	public void GUISetup() {		
		//Set up buttons		
		Button exitButton = new Button("Exit");
		exitButton.setAlignment(Pos.TOP_CENTER);		
		exitButton.setStyle("-fx-background-color:#cd0030");
		exitButton.setPrefSize(60, 30);
		exitButton.setOnAction(e -> exitProgram());
		
		Text speedText = new Text("Current Speed =>");
		Text changespeedText = new Text("Click to change the speed");
		
		String temp = speedChoices[currentSpeed];
		speedButton = new Button(temp);
		speedButton.setOnAction(s -> changeSpeed());
		
		Button playButton = new Button("Play");
		playButton.setPrefSize(60, 30);
		playButton.setStyle("-fx-background-color: #9ec13b;");
		playButton.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event){
				try {
					OSSetup();
				}
				catch(Exception E){
					System.out.println("There's nothing to show!!!!");		
				}
			}
		});
		
		
		//Set up GUI for Disks, Threads, Users
		gridpane.setAlignment(Pos.TOP_LEFT);
		primaryStage.setMinWidth(1200);
		primaryStage.setMinHeight(800);
		gridpane.add(playButton,0,0);
		gridpane.setHalignment(playButton,HPos.CENTER);
		
		gridpane.add(exitButton, 2, 0);
		gridpane.setHalignment(exitButton,HPos.CENTER);		
		
		gridpane.add(speedButton, 1, 0);
		gridpane.setHalignment(speedButton,HPos.CENTER);
		
		gridpane.add(speedText, 1, 0);
		gridpane.setHalignment(speedText,HPos.LEFT);
		gridpane.add(changespeedText, 1, 0);
		gridpane.setHalignment(changespeedText,HPos.RIGHT);
		
		gridpane.add(generateHeader("Users"), 0, 1);
		gridpane.add(generateHeader("Printers"), 2, 1);
		gridpane.add(generateHeader("Disks"), 1, 1);
		
		//setup List View of Printer
		listView1.setItems(observList1);
		listView1.setPrefSize(150,160);
		
		listView2.setItems(observList2);
		listView2.setPrefSize(150,160);
		
		listView3.setItems(observList3);
		listView3.setPrefSize(150,160);	
		
		printerPane.setVgap(20);
		//Set up Printer1
		printer1 = new Text("PRINTER 1");
		printerPane.add(listView1, 2, 0);
		
		printer1.setTextAlignment(TextAlignment.CENTER);
		printer1.setStyle("-fx-font: 20px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");
		printer1Rec.setWidth(100);
		printer1Rec.setHeight(50);
		printer1Rec.setFill(Color.WHITE);
		printer1Rec.setStroke(Color.BLACK);
		printerPane.add(printer1Rec, 1, 0);
		printerPane.add(printer1, 1, 0);	
		printerPane.setHalignment(printer1, HPos.CENTER);
		
		//Set up Printer2
		printer2 = new Text("PRINTER 2");		
		printerPane.add(listView2, 2, 1);		
		printer2.setTextAlignment(TextAlignment.CENTER);
		printer2.setStyle("-fx-font: 20px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");
		printer2Rec.setWidth(100);
		printer2Rec.setHeight(50);
		printer2Rec.setFill(Color.WHITE);
		printer2Rec.setStroke(Color.BLACK);
		printerPane.add(printer2Rec, 1, 1);
		printerPane.add(printer2, 1, 1);	
		printerPane.setHalignment(printer2, HPos.CENTER);
		
		//Set up Printer1
		printer3 = new Text("PRINTER 3");
		printerPane.add(listView3, 2, 2);
		printer3.setTextAlignment(TextAlignment.CENTER);
		printer3.setStyle("-fx-font: 20px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");
		printer3Rec.setWidth(100);
		printer3Rec.setHeight(50);
		printer3Rec.setFill(Color.WHITE);
		printer3Rec.setStroke(Color.BLACK);
		printerPane.add(printer3Rec, 1, 2);
		printerPane.add(printer3, 1, 2);	
		printerPane.setHalignment(printer3, HPos.CENTER);
		
		printerPane.setAlignment(Pos.CENTER);		
	}
	
	public VBox generateHeader (String headerText) {
		VBox box = new VBox();
		createBox DiskCategoryBox = new createBox();		
		Text header = new Text(headerText);
		header.setStyle("-fx-font: 30px Calibri;\r\n" + 
				"    -fx-fill: #004C99;" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .25;");
		StackPane stack = new StackPane();
		//DiskCategoryBox.widthProperty().bind(diskGP.widthProperty());
		
		stack.setAlignment(Pos.CENTER);
		stack.getChildren().setAll(header,DiskCategoryBox);
		//GridPane.setMargin(disks[0].diskStack, new Insets(20,0,15,0));
		//GridPane.setMargin(disks[1].diskStack, new Insets(15,0,20,0));
		if(headerText.equals("Disks"))
			box.getChildren().setAll(stack,diskPane);
			
			
		else if(headerText.equals("Printers"))
			box.getChildren().setAll(stack,printerPane);
		else
			box.getChildren().setAll(stack,userPane);
		return box;
	}
	
	public class createBox extends Rectangle {
		createBox(){
			setWidth(400);
	        setHeight(50);	                    
	        setFill(Color.rgb(117,141,141,.15) );
	        setStroke(Color.rgb(117,141,141,.75));
		}
	}
	
	public void changeSpeed() {
		if(currentSpeed >=3) {
			currentSpeed = 0;
		} else currentSpeed++;
		speedButton.setText(speedChoices[currentSpeed]);		
	}
	
	public void RunGUI() {
		primaryStage.setTitle("Basic Operating System");
		gridpane.setAlignment(Pos.CENTER);
		
		//Add start button and style
		Button startButton = new Button("Start");
		startButton.setStyle("-fx-background-color: #9ec13b;");
		startButton.setPrefSize(60, 30);
				
		Scene scene= new Scene(gridpane, 400, 400);
		welcomeText = new Text("Welcome to \nBasic Operating System!!!");
		Text studentInfo = new Text("By JONATHAN TRAN (#20843397)");
		studentInfo.setTextAlignment(TextAlignment.CENTER);
		studentInfo.setStyle("-fx-font: 25px Calibri;\r\n");
		welcomeText.setTextAlignment(TextAlignment.CENTER);
		welcomeText.setStyle("-fx-font: 35px Calibri;\r\n");
				
		gridpane.add(welcomeText, 0, 0);		
		gridpane.add(studentInfo, 0, 1);
		gridpane.setHalignment(studentInfo, HPos.CENTER);
		gridpane.add(startButton, 0, 2);
		gridpane.setHalignment(startButton, HPos.CENTER);
		gridpane.setStyle("-fx-background-color: #dddddd;");
		gridpane.setVgap(30);
		gridpane.setAlignment(Pos.CENTER);
		
		primaryStage.setScene(scene);
		primaryStage.setMinWidth(600);
		primaryStage.setMinHeight(600);
		
		primaryStage.show();
		startButton.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event){
				try {
					GUISetup();
					gridpane.getChildren().remove(startButton);
					gridpane.getChildren().remove(welcomeText);
					gridpane.getChildren().remove(studentInfo);
				}
				catch(Exception E){
					System.out.println("There's nothing to show!!!!");		
				}
			}
		});			
		
			
	}
	
	@Override
	public void start(Stage primaryStage) throws Exception {
		this.primaryStage = primaryStage;
		Platform.runLater( () -> {
			RunGUI();
		});
	
	}
	
	private void exitProgram() {
		primaryStage.close();
	}
}

class Disk {
	static final int NUM_SECTORS = 1024;
	StringBuffer sectors[] = new StringBuffer[NUM_SECTORS];
	int diskID;
	int freeSector;
	//Set up Disk GUI variable
	Text diskTitle;
	Text displayText;
	StackPane diskStack = new StackPane();
	StackPane userStack = new StackPane();
	Circle diskCircle = new Circle();
	Line line = new Line();
	
	Disk(int diskNumber) {
		this.diskID = diskNumber;
		this.diskTitle = new Text("Disk" + diskID);		
		
		//Draw the disk
		diskCircle.setRadius(60.0f);
		diskCircle.setFill(Color.WHITE);
		diskCircle.setStroke(Color.BLACK);		
		diskTitle.setStyle("-fx-font: 30px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");
		
		OS141.diskPane.add(diskCircle, 1, diskNumber-1);		
		OS141.diskPane.setHalignment(diskCircle,HPos.CENTER);
		OS141.diskPane.add(diskTitle, 1, diskNumber-1);
		OS141.diskPane.setHalignment(diskTitle,HPos.CENTER);
		OS141.diskPane.setAlignment(Pos.CENTER);
		OS141.diskPane.setVgap(20);
		OS141.diskPane.setMargin(diskCircle,new Insets(20));
		OS141.diskPane.setMargin(diskTitle,new Insets(20));
	}	
	

	public void resetDisk() {
		Platform.runLater( () -> {
			OS141.diskPane.getChildren().remove(diskStack);
			OS141.userPane.getChildren().remove(userStack);
			diskCircle.setFill(Color.WHITE);
			diskCircle.setStroke(Color.BLACK);
			diskTitle.setStyle("-fx-font: 30px Calibri;\r\n" + 
					"    -fx-fill: #000000" +";\r\n" + 
					"    -fx-stroke: black;\r\n" + 
					"    -fx-stroke-width: .5;");			
		});
		try {
			Thread.sleep(50);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	void write(int sector, StringBuffer data, int userNumber, String fileName)
	{				
		try {
			//Convert data to StringBuffer
			StringBuffer convertData = new StringBuffer(data.toString());
		    Thread.sleep((long) (400*OS141.speedOptions[OS141.currentSpeed]));
		    sectors[sector] = convertData;		    
		    //Set up GUI
		    resetDisk();
		    
		    displayText = new Text("USER " + userNumber +" is saving " + convertData.toString() + " to sector " + sector);		    
			
		    Platform.runLater( () -> {
				diskTitle.setStyle("-fx-font: 30px Calibri;\r\n" + 
						"    -fx-fill: #ff0000" +";\r\n" + 
						"    -fx-stroke: black;\r\n" + 
						"    -fx-stroke-width: .5;");
				displayText.setTextAlignment(TextAlignment.CENTER);
			    displayText.setStyle("-fx-font: 15px Calibri;\r\n" + 
						"-fx-fill:"+ OS141.UserColor[userNumber-1] + ";\r\n");
			    diskStack.getChildren().setAll(displayText);
			    diskStack.setAlignment(Pos.BOTTOM_CENTER);
			    OS141.diskPane.add(diskStack, 1, diskID - 1);
			    
			    Text temp = new Text("Saving to Disk " + diskID);
			    temp.setStyle("-fx-font: 15px Calibri;\r\n" + 
						"-fx-fill:"+ OS141.UserColor[userNumber-1] + ";\r\n");
			    userStack.getChildren().setAll(temp);
			    userStack.setAlignment(Pos.BOTTOM_CENTER);			    
			    OS141.userPane.add(userStack, 0, userNumber - 1);
			    
			    diskCircle.setFill(Color.valueOf(OS141.UserColor[userNumber-1]));
	    		});		    
		} catch (InterruptedException e) {
		    System.out.println("Thread has been interrupted");
		}		
	}
	void read(int sector, StringBuffer data, int printerID)
	{
		// thread sleep
		try {//						
			Thread.sleep((long) (400*OS141.speedOptions[OS141.currentSpeed]));
		    data.append(sectors[sector]);
		    
		} catch (InterruptedException e) {
		    System.out.println("Thread has been interrupted");
		}	
	}	
}

class UserThread extends Thread{
	StringBuffer userBuffer = new StringBuffer();
	File inputFile;
	String userID;
	FileInfo fileInfo;
	Disk currentDisk;
	String fileName;
	int currentDiskID;
	int currentDiskSector;
	int userNumber;
	//Set up GUI variable
	Text userName;
	Text displayText = new Text();
	Rectangle userRec = new Rectangle();	
	
	UserThread(int userNumber, File file)
	{
		this.inputFile = file;
		this.userID = "USER" + Integer.toString(userNumber);
		this.currentDiskID = -1; 
		this.currentDiskSector = -1; 
		this.userName = new Text(userID);
		this.userNumber = userNumber;
		
		//Draw user's rectangle
		userRec.setWidth(100);
		userRec.setHeight(100);
		userRec.setFill(Color.WHITE);
		userRec.setStroke(Color.BLACK);
		
		userName.setStyle("-fx-font: 30px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");
		
		OS141.userPane.add(userRec, 0, userNumber-1);
		OS141.userPane.setHalignment(userRec,HPos.CENTER);
		OS141.userPane.add(userName, 0, userNumber-1);
		OS141.userPane.setHalignment(userName,HPos.CENTER);
		OS141.userPane.setAlignment(Pos.CENTER);
		OS141.userPane.setVgap(20);
		OS141.userPane.setMargin(userRec,new Insets(20));
		OS141.userPane.setMargin(userName,new Insets(5));
		
	}
	
	public void resetUser() {		
		userRec.setFill(Color.WHITE);
		userRec.setStroke(Color.BLACK);		
		userName.setStyle("-fx-font: 30px Calibri;\r\n" + 
				"    -fx-fill: #000000" +";\r\n" + 
				"    -fx-stroke: black;\r\n" + 
				"    -fx-stroke-width: .5;");		
	}
	
	void readFile() throws InterruptedException,IOException
	{
		try (Scanner sc = new Scanner(inputFile)) {
		    //read each line			
			while (sc.hasNextLine()) {
		        String line = sc.nextLine();		        
		        //save line to userBuffer
		        userBuffer.append(line);
		        String text[] = userBuffer.toString().split(" ");
		        //Save line to disk
		        if(text[0].equals( ".save")) {
		        	currentDiskID = OS141.diskManager.request(); //request available disks
		        	fileName = text[1]; //File name		        	
		        	currentDisk = OS141.disks[currentDiskID];
		        	currentDiskSector = currentDisk.freeSector;
		        	fileInfo = new FileInfo(currentDiskID,currentDiskSector,0);
		        	resetUser();
		        	currentDisk.resetDisk();
		        }
		        //Stop saving to disk
		        else if(text[0].equals(".end")) {		        	
		        	OS141.diskManager.release(currentDiskID);
		        	OS141.DirectoryManager.enter(fileName, fileInfo);
		        	OS141.diskManager.setNextFreeDiskSector(currentDiskID,currentDiskSector,OS141.disks);
		        	currentDisk.resetDisk();
		        	resetUser();
		        	currentDiskID = -1;
		        	currentDiskSector = -1;
		        }
		        //print out file
		        else if(text[0].equals(".print")){
		        	PrintJobThread printJob = new PrintJobThread(fileName);
		        	printJob.start();
		        }
		        else {
		        	fileInfo.fileLength++;
		        	currentDisk.write(currentDiskSector, userBuffer, userNumber, fileName);
		        	currentDiskSector++;		        	  	
		        	
		        	Platform.runLater( () -> {
						userName.setStyle("-fx-font: 30px Calibri;\r\n" + 
								"    -fx-fill: #ff0000" +";\r\n" + 
								"    -fx-stroke: black;\r\n" + 
								"    -fx-stroke-width: .5;");										    
					    userRec.setFill(Color.valueOf(OS141.UserColor[userNumber-1]));
			    		});
		        }
		        userBuffer.delete(0, userBuffer.length());
		    }
		} catch (FileNotFoundException e) {
		    e.printStackTrace();
		}
	}
	
	public void run() {
		try {
			readFile();
		}
		catch(InterruptedException IE){
			System.out.println("InterruptedException");
		}
		catch(IOException IO){
			System.out.println("IO Ecxp");
		}
	}
}

class FileInfo {
	int diskNumber;
	int startingSector;
	int fileLength;
	FileInfo (int diskNo, int sector, int length)
	{
		this.diskNumber = diskNo;
		this.startingSector = sector;
		this.fileLength = length;
	}
	
	void printFileInfo() {
		System.out.println("Disk No: " + diskNumber + " | Starting sector: "
			+ startingSector + " | Length: " + fileLength);
	}
}

class ResourceManager{
	boolean isFree[];
	ResourceManager(int numOfItems){
		isFree = new boolean[numOfItems];
		for(int i = 0; i < isFree.length; ++i)
			isFree[i] = true;
	}
	synchronized int request()throws InterruptedException{
		while(true){
			for(int i = 0; i < isFree.length; ++i){
				if(isFree[i]){
					isFree[i] = false;
					return i;
				}
			}
			System.out.println("Thread (" + this.toString() + ") is waiting for resources....");
			this.wait(); //block until someone releases a Resource
		}
	}
	synchronized void release(int index){
		isFree[index] = true;
		this.notify(); //let a waiting thread run
		System.out.println("Thread (" + this.toString() + ") released resources.");
	}
}

class PrinterManager extends ResourceManager{	
	PrinterManager(int noOfPrinters) {
		super(noOfPrinters);
	}
}

class DiskManager extends ResourceManager{	
	DiskManager(int numOfDisks) {
		super(numOfDisks);
	}
	
	void setNextFreeDiskSector(int diskID, int diskSector, Disk disks[]) {
		disks[diskID].freeSector = diskSector;
	}

	class DirectoryManager {
		private Hashtable<String, FileInfo> T = 
		    new Hashtable<String, FileInfo>();
		void enter(String key, FileInfo file)
		{
			if(!T.containsKey(key)) {
				T.put(key,file);
			}
			else {
				System.out.println("File already existed.");
			}
		}
		FileInfo lookup(String key)
		{
			return T.get(key);
		}
	}
}

class PrintJobThread extends Thread{
	String fileName;
	int printerID;
	Printer currentPrinter;
	FileInfo fileInfo;	
	
	PrintJobThread(String fileName){
		this.fileName = fileName;
	}
	
	void requestPrinter() throws Exception  {	
			printerID = OS141.PrinterResource.request();
			currentPrinter = OS141.printers[printerID];	
	}
	
	public void run() {		
		try {
			//request available Printer
			requestPrinter();
			
			fileInfo = OS141.DirectoryManager.lookup(fileName);
			int startFile = fileInfo.startingSector;
			int endFile = startFile + fileInfo.fileLength;
			
			StringBuffer line = new StringBuffer();
			for(int i = startFile; i < endFile; i++)
			{			
				OS141.disks[fileInfo.diskNumber].read(i, line, printerID);
				OS141.printers[printerID].resetPrinter(printerID);
				OS141.printers[printerID].print(line);			
				
				System.out.println("Printing--------->" + line + ". To printer"+printerID);
				System.out.println("From---------> DISK"+fileInfo.diskNumber +"Sector:" + i);				
				if(printerID==1) {
					OS141.observList1.add(line.toString());
					
					Platform.runLater( () -> {
						OS141.printer1.setStyle("-fx-font: 20px Calibri;\r\n" + 
								"    -fx-fill: #ff0000" +";\r\n" + 
								"    -fx-stroke: black;\r\n" + 
								"    -fx-stroke-width: .5;");
						OS141.printer1Rec.setFill(Color.valueOf("#ffd700"));
					});			
					
				}
				else if(printerID==2) {
					OS141.observList2.add(line.toString());
					Platform.runLater( () -> {
						OS141.printer2.setStyle("-fx-font: 20px Calibri;\r\n" + 
								"    -fx-fill: #ff0000" +";\r\n" + 
								"    -fx-stroke: black;\r\n" + 
								"    -fx-stroke-width: .5;");
						OS141.printer2Rec.setFill(Color.valueOf("#ffd700"));
					});	
				}
				else {
					OS141.observList3.add(line.toString());					
					Platform.runLater( () -> {
						OS141.printer3.setStyle("-fx-font: 20px Calibri;\r\n" + 
								"    -fx-fill: #ff0000" +";\r\n" + 
								"    -fx-stroke: black;\r\n" + 
								"    -fx-stroke-width: .5;");
						OS141.printer3Rec.setFill(Color.valueOf("#ffd700"));
					});	
				}
				
				//delete the buffer
				line.delete(0, line.length());
			}
			OS141.PrinterResource.release(printerID);
			OS141.printers[printerID].resetPrinter(1);
			OS141.printers[printerID].resetPrinter(2);
			OS141.printers[printerID].resetPrinter(3);
		} 
		catch (Exception e) {}		
	}
}

class Printer {
	String printerNumber;
	int printerID;
	StackPane printerStack = new StackPane();
	Text printerTitle;		
	
	Printer(int i){
		this.printerNumber = "PRINTER" + Integer.toString(i);		
		this.printerID = i;
		this.printerTitle = new Text(printerNumber);
		
	}
	
	void resetPrinter(int printerID) {
		if(printerID == 1) {
			Platform.runLater( () -> {						
				OS141.printer1Rec.setFill(Color.WHITE);
				OS141.printer1Rec.setStroke(Color.BLACK);
				OS141.printer1.setStyle("-fx-font: 20px Calibri;\r\n" + 
						"    -fx-fill: #000000" +";\r\n" + 
						"    -fx-stroke: black;\r\n" + 
						"    -fx-stroke-width: .5;");			
			});
		}
		else if(printerID == 2) {
			Platform.runLater( () -> {						
				OS141.printer2Rec.setFill(Color.WHITE);
				OS141.printer2Rec.setStroke(Color.BLACK);
				OS141.printer2.setStyle("-fx-font: 20px Calibri;\r\n" + 
						"    -fx-fill: #000000" +";\r\n" + 
						"    -fx-stroke: black;\r\n" + 
						"    -fx-stroke-width: .5;");			
			});
		}
		else {
			Platform.runLater( () -> {						
				OS141.printer3Rec.setFill(Color.WHITE);
				OS141.printer3Rec.setStroke(Color.BLACK);
				OS141.printer3.setStyle("-fx-font: 20px Calibri;\r\n" + 
						"    -fx-fill: #000000" +";\r\n" + 
						"    -fx-stroke: black;\r\n" + 
						"    -fx-stroke-width: .5;");			
			});
		}
		
		try {
			Thread.sleep(50);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	void print(StringBuffer data) throws IOException, InterruptedException {		
		if(data != null) {
			FileWriter file = new FileWriter(printerNumber,true);
			BufferedWriter write = new BufferedWriter(file);
			
			Thread.sleep((long) (550*OS141.speedOptions[OS141.currentSpeed]));
			write.write(data.toString());
			write.newLine();
			write.flush();
			write.close();			
		}
		else
			System.out.println("PRINTER BUFFER IS NULL");
	}
}






