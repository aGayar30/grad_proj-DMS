#include <thread>
#include "threadsafequeue.h"
#include "basiccameracomponent.h"
#include "basicpreprocessingcomponent.h"
#include "facedetectioncomponent.h"
#include "DrowsinessComponent.h"
#include "commtcpcomponent.h"
#include "vehiclestatemanager.h"
#include "postprocessingcomponent.h"
#include "faultmanager.h"

class DMSManager {
public:
    DMSManager(ThreadSafeQueue<cv::Mat>& cameraQueue, ThreadSafeQueue<cv::Mat>& preprocessingQueue, ThreadSafeQueue<cv::Mat>& faceDetectionQueue, ThreadSafeQueue<cv::Mat>& drowsinessDetectionQueue,ThreadSafeQueue<cv::Mat>& tcpOutputQueue, int tcpPort, ThreadSafeQueue<CarState>& stateOutputQueue , ThreadSafeQueue<int>& postOutputQueue,ThreadSafeQueue<std::string>& commandsQueue,ThreadSafeQueue<std::string>& faultsQueue);
    ~DMSManager();

    bool startSystem();
    void stopSystem();
    bool initializeCamera(const std::string& source);
    bool initializeFaceDetection(const std::string& modelConfiguration, const std::string& modelWeights);
    bool initializeDrowsinessDetection();
    //bool initializeVehicleState(const std::string& steeringFilePath, const std::string& velocityFilePath);
    bool initializePostProcessing();
    void setCameraFPS(int fps);
    void setFaceFDT(int fdt);


    // function to handle the different types of commands send by the windows app
    void handlecommand(std::string& command);

    

private:
    BasicCameraComponent cameraComponent;
    BasicPreprocessingComponent preprocessingComponent;
    FaceDetectionComponent faceDetectionComponent;
    DrowsinessComponent drowsinessComponent;
    CommTCPComponent tcpComponent; 
    VehicleStateManager vehicleStateManager;
    PostProcessingComponent postProcessingComponent;
    FaultManager faultManager;

    ThreadSafeQueue<cv::Mat>& cameraQueue;
    ThreadSafeQueue<cv::Mat>& preprocessingQueue;
    ThreadSafeQueue<cv::Mat>& faceDetectionQueue;
    ThreadSafeQueue<cv::Mat>& drowsinessDetectionQueue;
    ThreadSafeQueue<cv::Mat> tcpOutputQueue;
    ThreadSafeQueue<CarState>& stateOutputQueue;
    ThreadSafeQueue<int>& postOutputQueue;



    ThreadSafeQueue<std::string>& commandsQueue;
    ThreadSafeQueue<std::string>& faultsQueue;


    std::thread cameraThread;
    std::thread preprocessingThread;
    std::thread faceDetectionThread;
    std::thread drowsinessThread;
    std::thread tcpThread; 
    std::thread vehicleStateThread;
    std::thread postProcessingThread; 
    std::thread commandsThread; 
    std::thread faultsThread; 

    int tcpPort; 
    bool running;

    void cameraLoop();
    void preprocessingLoop();
    void faceDetectionLoop();
    void drowsinessLoop();
    void commtcpLoop(); 
    void vehicleStateLoop(); 
    void postprocessingLoop(); 
    void commandsLoop();
    void faultsLoop();

};

