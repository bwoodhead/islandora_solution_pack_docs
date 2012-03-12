<?php


class DocumentProcessor {
    
  /**
   * Create thumbnail handler callback from a content model
   * @param type $parameterArray
   * @param type $dsid
   * @param type $file
   * @param type $file_ext
   * @return type 
   */
  public function createThumbnailFromPDFHandler($parameterArray, $dsid, $file, $file_ext) {
    $height = $parameterArray['height'];
    $width = $parameterArray['width'];
    
    return $this->createThumbnailFromPDF($file, $width, $height, $file_ext);
  }
    
  /**
   * Create a thumbnail of a pdf
   * @param type $file
   * @param type $width
   * @param type $height
   * @param type $file_ext
   * @return boolean 
   */
  private function createThumbnailFromPDF($file, $width, $height, $file_ext) {
      
    $dsid = 'TN';
    $file_suffix = '_' . $dsid . '.' . $file_ext;
    $returnValue = TRUE;
    //system("convert $file\[0\] -thumbnail 128x128 $uploaddir$thumb");
    // Use this for Linux.
    if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
      
    }
    elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
      $cmdline = "/usr/local/bin/convert \"$file\"\[0\] -colorspace RGB -thumbnail $width" . "x$height \"$file$file_suffix\"";
    }
    elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
      // Use this for Mac OS X (MAMP)
      $cmdline = "sips -s format jpeg \"$file\" -z $height $height --out \"$file$file_suffix\" >/dev/null";
    }
    else {
      $cmdline = "convert \"$file\"\[0\] -colorspace RGB -thumbnail " . $width . "x" . $height . " \"$file$file_suffix\"";
    }

    system($cmdline, $returnValue);

    $var = $file . $file_suffix . ' returnvalue= ' . $returnValue;

    if ($returnValue == '0') {
      $_SESSION['fedora_ingest_files']["$dsid"] = $file . $file_suffix;
      return TRUE;
    }
    else {
      return $returnValue;
    }
  }
    /**
     * Convert to pdf then ingest 
     * @param string $args
     * @param type $dsid
     * @param type $file
     * @param type $file_ext
     * @return boolean 
     */
/**
    public function convertDocumentToPDFHandler($args=NULL, $dsid, $file, $return_type) {
        
        // Convert the document to a pdf
        $dest_file = convertDocumentToPDF($file);
        
        // Check to see if it worked
        if ( $dest_file != false ) {
            
            // Store the file in the session
            $_SESSION['fedora_ingest_files']["$dsid"] = $dest_file;
            
            // Return sucess
            return true;
        } 
        
        // Return failed
        return false;
    }
*/    
    /**
     * Convert to pdf then create a thumbnail
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $file_ext 
     */
/**    
    public function createThumbnailFromDocumentHandler($args, $dsid, $file, $return_type) {

        // Get the parameters
        $width = $args['width'];
        $height = $args['height'];

        // Convert the document to pdf
        $dest_file = convertDocumentToPDF($file);
        
        // Create a thumbnail of the pdf
        $thumbnail = creatPDFThumbnail($dest_file, $width, $height, $return_type);
        
        // Check to see if the thumbnail is valid
        if ( $thumbnail != false ) {
            
            // Store the thumbnail in the session
            $_SESSION['fedora_ingest_files']["$dsid"] = $thumbnail;
            
            // Return success
            return true;
        } 
        
        // Return failed
        return false;        
    }
*/    
    /**
    * Create thumbnail from pdf
    * @param type $parameterArray
    * @param type $dsid
    * @param type $file
    * @param type $file_ext
    * @return boolean 
    */
    /**
    public function createThumbnailFromPDFHandler($parameterArray, $dsid, $file, $file_ext) {
        $height = $parameterArray['height'];
        $width = $parameterArray['width'];
        $file_suffix = '_' . $dsid . '.' . $file_ext;
        $returnValue = TRUE;
        //system("convert $file\[0\] -thumbnail 128x128 $uploaddir$thumb");
        // Use this for Linux.
        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {

        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
            $cmdline = "/usr/local/bin/convert \"$file\"\[0\] -colorspace RGB -thumbnail $width" . "x$height \"$file$file_suffix\"";
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
        // Use this for Mac OS X (MAMP)
            $cmdline = "sips -s format jpeg \"$file\" -z $height $height --out \"$file$file_suffix\" >/dev/null";
        }
        else {
            $cmdline = "convert \"$file\"\[0\] -colorspace RGB -thumbnail " . $width . "x" . $height . " \"$file$file_suffix\"";
        }

        system($cmdline, $returnValue);
        //system("convert $file\[0\] -thumbnail 128x128 $uploaddir$thumb");
        $var = $file . $file_suffix . ' returnvalue= ' . $returnValue;

        if ($returnValue == '0') {
            $_SESSION['fedora_ingest_files']["$dsid"] = $file . $file_suffix;
            return TRUE;
        }
        else {
            return $returnValue;
        }
    } 
    */
    
    
    /**
     * Convert the document to a pdf
     * @param type $file
     * @return boolean|string 
     */
/**
    private function convertDocumentToPDF($file) {
        
        // Create the return file name
        $dest_file = dirname($file) . basename($file) . '.pdf';

        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
            
            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        else {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }

        // Build the command to convert the file to a pdf
        $cmdline = $application + ' --headless --convert-to pdf ' + $file;
        $return_value = true;
        
        // Run the command
        system($cmdline, $return_value);

        // Check to see if the call failed
        if ( $returnValue == false ) {
            
            // Return failed
            return false;
        }
        
        // Return the file
        return $dest_file;
    }
*/
    
    /**
     * Create a thumbnail from a pdf
     * @param type $file
     * @param type $width
     * @param type $height
     * @param type $return_type
     * @return boolean|string 
     */
    /**
    private function createThumbnail($file, $width, $height, $return_type) {
    }
     */
    
}   

?>
