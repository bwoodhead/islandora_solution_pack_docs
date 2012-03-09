<?php


class DocumentProcessor 
{
    private $pid;
    
    
    public function __construct($pid=null) {
    }
    
    /**
     * Ingest is a hook called from the content model 
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $file_ext
     * @return boolean|string 
     */
    public function ingest($args, $dsid, $file, $file_ext) {
        
        $this->createDerivatives($args, $dsid, $file, $file_ext);
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
    
    /**
     * Create the derivatives
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $file_ext
     * @return boolean|string 
     */
    public function createDerivatives($args, $dsid, $file, $file_ext) {
        
        $system = getenv('System');
        $file_suffix = '_' . $dsid . '.' . $file_ext;

        $returnValue = TRUE;
        $output = array();

        $destDir = dirname($file) . '/work';
        $destFile = $destDir . '/' . basename($file) . $file_suffix;
        if (!is_dir($destDir)) {
            @mkdir($destDir);
        }

        if (!file_exists($destFile)) {
            exec('convert -resize ' . $width . 'x' . $height . ' -quality 85  "' . $file . '"[0] -strip "' . $destFile . '" 2>&1 &', $output, $returnValue);
        }
        else {
            $returnValue = '0';
        }

        if ($returnValue == '0') {
            $_SESSION['fedora_ingest_files']["$dsid"] = $destFile;
            return TRUE;
        }
        else {
            return $returnValue;
        }
    }

}

?>
