<?php


class DocumentProcessor 
{
    
    /**
     * Ingest a pdf 
     */
    public function ingestPDF($args, $dsid, $file, $file_ext) {
        
        // Copy the pdf 
        $_SESSION['fedora_ingest_files']["$dsid"] = $file;
        return TRUE;
    }
    
    /**
     * Convert to pdf then ingest 
     */
    public function convertAndIngestPDF($args, $dsid, $file, $file_ext) {
        
        $returnValue = TRUE;
        $output = array();

        $destFile = dirname($file) . basename($file) . '.' . $file_suffix;
        
        $application = '';
        $args ='--headless --convert-to PDF ';

        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
            $application = '';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
            $application = '';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
           $application = '';
        }
        else {
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }

        // Create the file
        system($application. " " . $args . " " . $file, $returnValue);

        if ($returnValue == '0') {
            $_SESSION['fedora_ingest_files']["$dsid"] = $destFile;
            return TRUE;
        }
        else {
            return $returnValue;
        }        
    }
    
    /**
     * Create the thumbnail
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $file_ext
     * @return boolean|string 
     */
    public function createThumbnail($args, $dsid, $file, $file_ext) {

        // Get the width and height from the arguments
        $height = $args['height'];
        $width = $args['width'];
        
        // Get the file from the session
        $file = $_SESSION['fedora_ingest_files']["$dsid"];

        $file_suffix = '_' . $dsid . '.' . $file_ext;
        $returnValue = TRUE;

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
     * Display Thumbnail is a hook called from the content model 
     */
    public function displayThumbnail() {
        
        global $base_url;
        global $base_path;
        global $user;
        
        module_load_include('inc', 'fedora_repository', 'api/fedora_item');
        
        $objectHelper = new ObjectHelper();
        
        $item = new Fedora_Item($this->pid);
        
        if (key_exists('TN', $item->datastreams)) {
            $tn_url = $base_url . '/fedora/repository/' . $item->pid . '/TN';
        }
        else {
            $tn_url = $base_path . drupal_get_path('module', 'fedora_repository') . '/images/Crystal_Clear_app_download_manager.png';
        }

        $dl_link = l('<div  style="float:left; padding: 10px"><img src="' . $tn_url . '"><br />View Document</div>', 'fedora/repository/' . $this->pid . '/OBJ', array('html' => TRUE));

        $tabset = array();

        $tabset['first_tab'] = array(
            '#type' => 'tabpage',
            '#title' => t('PDF'),
            '#content' => $dl_link,
        );

        $tabset['second_tab'] = array(
            '#type' => 'tabpage',
            '#title' => t('Read Online'),
            '#content' => "<iframe src=\"http://docs.google.com/viewer?url=" . $base_url . '/fedora/repository/' .
            $this->pid . '/OBJ/preview.pdf' . "&embedded=TRUE\" style=\"width:600px; height:500px;\" frameborder=\"0\"></iframe>"
        );

        // Render the tabset.
        return $tabset;
    }
}

?>
