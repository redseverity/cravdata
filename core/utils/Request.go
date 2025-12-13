package utils

import (
	"crypto/tls"
	"net/http"
	"time"
)

// URLCheckResult holds the result of checking a URL
type URLCheckResult struct {
	URL      string `json:"url"`
	Verified bool   `json:"verified"`
	Status   int    `json:"status"`
	Error    string `json:"error,omitempty"`
}

func Request(url string, timeout int) URLCheckResult {
	// Custom transport to skip invalid HTTPS certs
	transport := &http.Transport{
		TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
	}

	client := http.Client{
		Timeout:   time.Duration(timeout) * time.Second,
		Transport: transport,
	}

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return URLCheckResult{
			URL:      url,
			Verified: false,
			Status:   0,
			Error:    err.Error(),
		}
	}

	// Set a common User-Agent to avoid being blocked
	req.Header.Set("User-Agent", "Mozilla/5.0 (compatible; URLChecker/1.0)")

	resp, err := client.Do(req)
	if err != nil {
		return URLCheckResult{
			URL:      url,
			Verified: false,
			Status:   0,
			Error:    err.Error(),
		}
	}
	defer resp.Body.Close()

	verified := resp.StatusCode >= 200 && resp.StatusCode < 400

	return URLCheckResult{
		URL:      url,
		Verified: verified,
		Status:   resp.StatusCode,
	}
}
