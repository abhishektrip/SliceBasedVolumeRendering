#View- aligned slicing. 
  1.	Load 3D volume data into a 3D texture. 
  2.	A unit cube is scaled with the volumes dimension. 
  3.	The volume is divided into n (sampling rate) slices in the z -direction. 
  4.	The slices are view – aligned ( in this case in the X-Y plane) and stack up in the negative z direction. 
  5.	To create view -aligned slices, I used a rotation matrix which transforms the texture coordinates. This way, the slices (unit quad) stays in the same position and only the texture of the slice changes. 
  6.	The texture coordinates are transformed in the vertex shader. 
  7.	The 3D Texture uses the GL_CLAMP_TO_BORDER clamping mode to avoid artifacts due to transformation of the texture coordinates. 

#Transfer function:
  1.	Uses a manual array of points to setup a range for colors & alpha for 1D transfer function. 
  2.	These points are fit onto a cubic spline to smoothly fit them. 
  3.	The value form the 3D Texture is used to look-up color in the Fragment Shader. 
  4.	Adding a UI to manipulate the Tranfer function would be hugely beneficial. 
#How to use application:
  1.	cd to the exe folder inside SliceBasedVolumeRendering.
  2.	Use the following commands to load and render the scenes.  (Or use the batch files in the folder)
        a. Bonsai – greyscale (figure 1,2,3,4)
          SliceBasedVolumeRendering.exe BONSAI_OPACITY
        b. Bonsai – using Transfer function (figure 5,6,7,8)
          SliceBasedVolumeRendering.exe BONSAI_TF
        c. Foot – greyscale (figure 9,10)
          SliceBasedVolumeRendering.exe FOOT_OPACITY
        d. Foot – using transfer function (figure 11,12)
           SliceBasedVolumeRendering.exe FOOT_TF
        e. Anuerysm – greyscale (figure 13,14)
          SliceBasedVolumeRendering.exe ANUERYSM_OPACITY
        f. Anuerysm – using transfer function (figure 15,16)
          SliceBasedVolumeRendering.exe ANUERYSM_TF
   3.	Use A & R keys to rotate the volume on the Y-axis . Esc key to exit the application. 


