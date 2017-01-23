#include "PatternProjectAndCapture.h"

extern string configFileName;

void initialize()
{

	FileStorage configFile(configFileName, FileStorage::READ);

	configFile["Number of fringe patterns"] >> nFringePatterns;	
	configFile["Number of vertical gray coded patterns"] >> nGrayCodedPatternsVertical;
	configFile["Number of horizontal gray coded patterns"] >> nGrayCodedPatternsHorizontal;
	string rootOutputDirectory, fileLocation;
	configFile["Output directory"] >> rootOutputDirectory;

	for(unsigned int i = 0; i < nFringePatterns; i++)
        {
        	fileLocation << rootOutputDir << "/FringePatterns/Vertical/Pattern" << i << ".bmp";
        	projectedFringePatternsVertical[i] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);
       		
		fileLocation << rootOutputDir << "/FringePatterns/Horizontal/Pattern" << i << ".bmp";
        	projectedFringePatternsHorizontal[i] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);

       	}
        
        for(unsigned int j = 0; j < nGrayCodedPatternsVertical + 1; j++)
        {
		fileLocation << rootOutputDir << "/CodedPatterns/GrayCoded/Vertical/Pattern" << j << ".bmp";
        	projectedGrayCodedPatternsVertical[j] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);

	        fileLocation << rootOutputDir << "/CodedPatterns/GrayCoded/Vertical/InversePattern" << j << ".bmp";
        	projectedInverseGrayCodedPatternVertical[j] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);
        }

        for(unsigned int k = 0; k < nGrayCodedPatternsHorizontal + 1; k++)
        {
		fileLocation << rootOutputDir << "/CodedPatterns/GrayCoded/Horizontal/Pattern" << k << ".bmp";
        	projectedGrayCodedPatternsHorizontal[k] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);

	        fileLocation << rootOutputDir << "/CodedPatterns/GrayCoded/Horizontal/InversePattern" << k << ".bmp";
        	projectedInverseGrayCodedPatternHorizontal[k] = imread(fileLocation, CV_LOAD_IMAGE_GRAYSCALE);
        }

      
	return;
}

/*

//This function will project the pattern using projector.
void projectAndCapture()
{

    char pattern_name[15];

    //cap=cvQueryFrame(camera);//null frame.(CORRECT THIS FUNCTION:PENDING ASSIGNMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)


    //i want live preview & capture.
    bool capture_next=false;

    IplImage*temp_proj_pattern=cvCreateImage(cvSize(Projector_imagewidth,Projector_imageheight),8,1);

    IplImage*undist_cap=cvCreateImage(cvSize(Camera_imagewidth,Camera_imageheight),IPL_DEPTH_8U,3);

    if(pattern_type==0)
        sprintf(pattern_name,"vertical");

    else
        sprintf(pattern_name,"horizontal");






    printf("\nProjecting %s phase shifted fringe patterns...\n",pattern_name);


    /// Project & capture fringe patterns...
    for(int i=0; i<number_of_patterns_fringe; i++)
    {
        cvUndistort2(projected_image_set_fringe[i],temp_proj_pattern,proj_intrinsic_mat,proj_dist_vect);

        //while(capture_next!=true)
        // {
        cvScale(projected_image_set_fringe[i], projected_image_set_fringe[i], 2.*(proj_gain/100.), 0);
        cvShowImage("Projector_pattern",projected_image_set_fringe[i]);
        cvCopyImage(temp_proj_pattern,projected_image_set_fringe[i]);//for next iteration.

        //cap=cvQueryFrame(camera);
        //mainloop(cap);
        preview_and_capture();
        //cvScale(cap, cap, 2.*(cam_gain/100.), 0);

        //cvShowImage("Camera_view",cap);

        //if(cvWaitKey(30)=='c')
        //{
        // capture_next=true;

        if(pattern_type==0)//vertical.
        {
            sprintf(filename,"Captured_patterns/Fringe_patterns/Vertical/Original/Captured_image_%d.bmp",i);

            //cap=camera_capture(filename);
            //cap=cvQueryFrame(camera);
            //mainloop(cap);
            //cvWaitKey(30);

            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Fringe_patterns/Vertical/Undistorted/Captured_image_%d.bmp",i);
            cvSaveImage(filename,undist_cap);

        }

        else //horizontal
        {
            sprintf(filename,"Captured_patterns/Fringe_patterns/Horizontal/Original/Captured_image_%d.bmp",i);
            //cap=camera_capture(filename);
            //cap=cvQueryFrame(camera);
            // mainloop(cap);
            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Fringe_patterns/Horizontal/Undistorted/Captured_image_%d.bmp",i);
            cvSaveImage(filename,undist_cap);
        }
        //  }


        //else
        //   capture_next=false;//try again user still not satisfied.
        // }

        //capture_next=false;//for the next loop.
        printf("\nCaptured %d of %d frame!!\n",i+1,number_of_patterns_fringe);
        cvReleaseImage(&cap);
    }



    /// Project & capture gray coded patterns...
    if(pattern_type==0)
    {
        for(int j=0; j<number_of_patterns_binary_vertical+1; j++)
        {
            ///Gray coded
            cvUndistort2(projected_image_set_gray[j],temp_proj_pattern,proj_intrinsic_mat,proj_dist_vect);

            cvScale(projected_image_set_gray[j], projected_image_set_gray[j], 2.*(proj_gain/100.), 0);
            cvShowImage("Projector_pattern",projected_image_set_gray[j]);
            cvCopyImage(temp_proj_pattern,projected_image_set_gray[j]);

            preview_and_capture();

            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Coded_patterns/Gray_coded/Vertical/Undistorted/Captured_image_%d.bmp",j);
            cvSaveImage(filename,undist_cap);

            ///Inverse gray coded
            cvUndistort2(projected_image_set_gray_inverse[j],temp_proj_pattern,proj_intrinsic_mat,proj_dist_vect);
            cvScale(projected_image_set_gray_inverse[j], projected_image_set_gray_inverse[j], 2.*(proj_gain/100.), 0);
            cvShowImage("Projector_pattern",projected_image_set_gray_inverse[j]);
            cvCopyImage(temp_proj_pattern,projected_image_set_gray_inverse[j]);

            preview_and_capture();

            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Coded_patterns/Gray_coded/Vertical/Undistorted/inverse_Captured_image_%d.bmp",j);
            cvSaveImage(filename,undist_cap);


            printf("\nCaptured %d of %d frame!!\n",j+1,number_of_patterns_binary_vertical);
            cvReleaseImage(&cap);
        }

    }


    if(pattern_type==1)
    {

        for(int j=0; j<number_of_patterns_binary_horizontal+1; j++)
        {
            ///Gray coded
            cvUndistort2(projected_image_set_gray[j],temp_proj_pattern,proj_intrinsic_mat,proj_dist_vect);

            cvScale(projected_image_set_gray[j], projected_image_set_gray[j], 2.*(proj_gain/100.), 0);
            cvShowImage("Projector_pattern",projected_image_set_gray[j]);
            cvCopyImage(temp_proj_pattern,projected_image_set_gray[j]);

            preview_and_capture();

            sprintf(filename,"Captured_patterns/Coded_patterns/Gray_coded/Horizontal/Original/Captured_image_%d.bmp",j);

            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Coded_patterns/Gray_coded/Horizontal/Undistorted/Captured_image_%d.bmp",j);
            cvSaveImage(filename,undist_cap);



            ///Inverse gray coded
            cvUndistort2(projected_image_set_gray_inverse[j],temp_proj_pattern,proj_intrinsic_mat,proj_dist_vect);

            cvScale(projected_image_set_gray_inverse[j], projected_image_set_gray_inverse[j], 2.*(proj_gain/100.), 0);
            cvShowImage("Projector_pattern",projected_image_set_gray_inverse[j]);
            cvCopyImage(temp_proj_pattern,projected_image_set_gray_inverse[j]);

            preview_and_capture();

            cvUndistort2(cap,undist_cap,cam_intrinsic_mat,cam_dist_vect);
            sprintf(filename,"Captured_patterns/Coded_patterns/Gray_coded/Horizontal/Undistorted/inverse_Captured_image_%d.bmp",j);
            cvSaveImage(filename,undist_cap);

            printf("\nCaptured %d of %d frame!!\n",j+1,number_of_patterns_binary_horizontal);
            cvReleaseImage(&cap);


        }

    }

    return;
}


*/

void projectAndCapturePatterns()
{
    initialize();	    
    projectAndCapture();

    return;
}



